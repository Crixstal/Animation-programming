#include "Skeleton.h"

#include "Engine.h"
#include "stdafx.h"

void Skeleton::Init()
{
	for (int i = 0; i < GetSkeletonBoneCount() - 7; i++) // - 7 to remove IK
	{
		skeleton.push_back(std::make_shared<Bone>());

		skeleton[i]->name = GetSkeletonBoneName(i);
		skeleton[i]->index = i;

		if (GetSkeletonBoneParentIndex(i) == -1)
			skeleton[i]->parent = nullptr;
		else
			skeleton[i]->parent = skeleton[GetSkeletonBoneParentIndex(i)].get();

		GetSkeletonBoneLocalBindTransform(i, skeleton[i]->pos.x, skeleton[i]->pos.y, skeleton[i]->pos.z,
			skeleton[i]->rot.w, skeleton[i]->rot.x, skeleton[i]->rot.y, skeleton[i]->rot.z);

		posBindPose.push_back(skeleton[i]->pos);
		rotBindPose.push_back(skeleton[i]->rot);

		printf("bone %d name: %s\n", skeleton[i]->index, skeleton[i]->name);
	}
}

void Skeleton::MoveBone(const int indexBone, const quat& rotation, const float& translation, const float& speed)
{
	if (indexBone < 0 || indexBone > GetBonesNumber())
		return;

	skeleton[indexBone]->rot = quatSlerp(skeleton[indexBone]->rot, skeleton[indexBone]->rot * rotation, speed);
	//skeleton[indexBone]->pos = lerp(skeleton[indexBone]->pos, skeleton[indexBone]->pos + translation, speed);
}

const float* Skeleton::GetBonesMatrix(const std::vector<std::shared_ptr<Bone>>& animTransforms)
{
	matrix = new float[(GetBonesNumber()) * sizeof(Bone)];

	for (int i = 0; i < GetBonesNumber(); i++)
		memcpy(&matrix[i * (sizeof(mat4) / sizeof(float))], skeleton[i]->GetMatrix(animTransforms).e, sizeof(mat4));

	return matrix;
}

const void Skeleton::DrawWithAnim(const float& alpha, const std::vector<std::shared_ptr<Bone>>& currAnim, const std::vector<std::shared_ptr<Bone>>& nextAnim)
{
	for (auto& bone : skeleton)
	{
		bone->pos += lerp(currAnim[bone->index]->pos, nextAnim[bone->index]->pos, alpha);
		bone->rot *= quatSlerp(currAnim[bone->index]->rot, nextAnim[bone->index]->rot, alpha);
	}

	Draw();

	ResetSkeleton();
}

const void Skeleton::Draw()
{
	for (int i = 2; i < GetBonesNumber(); i++)
	{
		vec3 joint1 = skeleton[i]->locToGlobVec();
		vec3 joint2 = skeleton[i]->parent->locToGlobVec();

		DrawLine(joint1.x, joint1.y + offset, joint1.z,
				 joint2.x, joint2.y + offset, joint2.z,
				 0.f, 0.f, 1.f);
	}
}

const void Skeleton::ResetSkeleton()
{
	for (auto& bone : skeleton)
	{
		bone->pos = posBindPose[bone->index];
		bone->rot = rotBindPose[bone->index];
	}
}
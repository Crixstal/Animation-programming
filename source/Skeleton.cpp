#include "Skeleton.h"

#include "Engine.h"
#include "stdafx.h"

void Skeleton::Init()
{
	for (int i = 0; i < GetSkeletonBoneCount() - 7; i++) // - 7 to remove IK
	{
		bones_base.push_back(std::make_shared<Bone>());

		bones_base[i]->name = GetSkeletonBoneName(i);
		bones_base[i]->index = i;

		if (GetSkeletonBoneParentIndex(i) == -1)
			bones_base[i]->parent = nullptr;
		else
			bones_base[i]->parent = bones_base[GetSkeletonBoneParentIndex(i)].get();

		GetSkeletonBoneLocalBindTransform(i, bones_base[i]->pos.x, bones_base[i]->pos.y, bones_base[i]->pos.z,
								bones_base[i]->rot.w, bones_base[i]->rot.x, bones_base[i]->rot.y, bones_base[i]->rot.z);

		printf("bone %d name: %s\n", bones_base[i]->index, bones_base[i]->name);
	}

	for (auto& bone : bones_base)
		bones_anim.push_back(std::make_shared<Bone>(*bone.get()));
}

void Skeleton::Draw()
{
	for (int i = 2; i < GetBonesNumber() - 1; i++)
	{
		vec3 joint1 = bones_anim[i]->locToGlobVec();
		vec3 joint2 = bones_anim[i]->parent->locToGlobVec();

		DrawLine(joint1.x, joint1.y + offset, joint1.z,
				 joint2.x, joint2.y + offset, joint2.z,
				 0.f, 0.f, 1.f);
	}
}

void Skeleton::MoveBone(const int indexBone, const quat& rotation, const float& translation, const float& speed)
{
	if (indexBone < 0 || indexBone > GetBonesNumber())
		return;

	bones_base[indexBone]->rot = quatSlerp(bones_base[indexBone]->rot, bones_base[indexBone]->rot * rotation, speed); // fonctionne que si bones_base
	//bones_anim[indexBone]->pos = lerp(bones_anim[indexBone]->pos, bones_anim[indexBone]->pos + translation, speed);
}

const float* Skeleton::GetBonesMatrix(const std::vector<std::shared_ptr<Bone>>& animTransforms)
{
	float* matrix = new float[(GetBonesNumber()) * sizeof(Bone)];

	for (int i = 0; i < GetBonesNumber(); i++)
		memcpy(&matrix[i * (sizeof(mat4) / sizeof(float))], bones_base[i]->GetMatrix(animTransforms).e, sizeof(mat4));

	return matrix;
}

const void Skeleton::animSkel(const float& speed, const std::vector<std::shared_ptr<Bone>>& currAnim, const std::vector<std::shared_ptr<Bone>>& nextAnim)
{
	for (auto& bone : bones_anim)
	{
		bone->pos = bones_base[bone->index]->pos + lerp(currAnim[bone->index]->pos, nextAnim[bone->index]->pos, speed);
		bone->rot = bones_base[bone->index]->rot * quatSlerp(currAnim[bone->index]->rot, nextAnim[bone->index]->rot, speed);
	}
}
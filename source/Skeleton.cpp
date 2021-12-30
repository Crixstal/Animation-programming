#include "Skeleton.h"

#include "Engine.h"
#include "stdafx.h"

void Skeleton::Init()
{
	for (int i = 0; i < GetSkeletonBoneCount() - 7; i++) // - 7 to remove IK
	{
		bones_base.push_back(std::make_shared<Bone>());
		Bone& currentBone = *bones_base[i].get();

		currentBone.name = GetSkeletonBoneName(i);
		currentBone.index = i;

		if (GetSkeletonBoneParentIndex(i) == -1)
			currentBone.parent = nullptr;
		else
			currentBone.parent = bones_base[GetSkeletonBoneParentIndex(i)].get();

		GetSkeletonBoneLocalBindTransform(i, currentBone.pos.x, currentBone.pos.y, currentBone.pos.z,
							currentBone.rot.w, currentBone.rot.x, currentBone.rot.y, currentBone.rot.z);

		printf("bone %d name: %s\n", currentBone.index, currentBone.name);
	}

	for (auto& bone : bones_base)
		bones_anim.push_back(std::make_shared<Bone>(*bone.get()));
}

void Skeleton::Draw()
{
	for (int i = 2; i < bones_anim.size() - 1; i++)
	{
		vec3 joint1 = bones_anim[i]->locToGlobVec(bones_anim[i]->pos);
		vec3 joint2 = bones_anim[i]->parent->locToGlobVec(bones_anim[i]->parent->pos);

		DrawLine(joint1.x, joint1.y + offset, joint1.z,
				 joint2.x, joint2.y + offset, joint2.z,
				 0.f, 0.f, 1.f);
	}
}

void Skeleton::MoveBone(const int indexBone, const quat& rotation, const float& speed)
{
	if (indexBone < 0 || indexBone > bones_base.size())
		return;

	bones_base[indexBone]->rot = quatSlerp(bones_base[indexBone]->rot, bones_base[indexBone]->rot * rotation, speed);
}

const float* Skeleton::GetBonesMatrix(const std::vector<std::shared_ptr<Bone>>& animTransforms)
{
	float* matrix = new float[(bones_base.size()) * sizeof(Bone)];

	for (int i = 0; i < bones_base.size(); i++)
		memcpy(&matrix[i * (sizeof(mat4) / sizeof(float))], bones_base[i]->GetMatrix(animTransforms, bones_base).e, sizeof(mat4));

	return matrix;
}

const void Skeleton::animSkel(const char* animName, const int currKeyFrame, const float& alpha, const std::vector<std::shared_ptr<Bone>>& currAnim, const std::vector<std::shared_ptr<Bone>>& nextAnim)
{
	for (auto& bone : bones_anim)
	{
		GetAnimLocalBoneTransform(animName, bone->index, currKeyFrame % GetAnimKeyCount(animName), currAnim[bone->index]->pos.x, currAnim[bone->index]->pos.y, currAnim[bone->index]->pos.z,
									currAnim[bone->index]->rot.w, currAnim[bone->index]->rot.x, currAnim[bone->index]->rot.y, currAnim[bone->index]->rot.z);
		
		GetAnimLocalBoneTransform(animName, bone->index, (currKeyFrame + 1) % GetAnimKeyCount(animName), nextAnim[bone->index]->pos.x, nextAnim[bone->index]->pos.y, nextAnim[bone->index]->pos.z,
									nextAnim[bone->index]->rot.w, nextAnim[bone->index]->rot.x, nextAnim[bone->index]->rot.y, nextAnim[bone->index]->rot.z);

		bone->pos = bones_anim[bone->index]->pos + lerp(currAnim[bone->index]->pos, nextAnim[bone->index]->pos, alpha);
		bone->rot = bones_anim[bone->index]->rot * quatSlerp(currAnim[bone->index]->rot, nextAnim[bone->index]->rot, alpha);
	}
}
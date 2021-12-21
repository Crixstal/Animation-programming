#include "Skeleton.h"

#include "Engine.h"
#include "stdafx.h"

void Skeleton::Set()
{
	Bone& currentBone = Bone();

	for (int i = 0; i < GetSkeletonBoneCount() - 7; i++) // - 7 to remove IK
	{
		currentBone.name = GetSkeletonBoneName(i);
		currentBone.index = i;

		if (GetSkeletonBoneParentIndex(i) == -1)
			currentBone.parent = nullptr;
		else
			currentBone.parent = &bones_base[GetSkeletonBoneParentIndex(i)];

		GetSkeletonBoneLocalBindTransform(i, currentBone.pos.x, currentBone.pos.y, currentBone.pos.z,
							currentBone.rot.w, currentBone.rot.x, currentBone.rot.y, currentBone.rot.z);

		bones_base.push_back(currentBone);

		bones_base[i].parent = currentBone.parent;

		printf("bone %d name: %s\n", bones_base[i].index, bones_base[i].name);
	}

	bones = bones_base;
}

void Skeleton::Draw()
{
	for (int i = 2; i < bones_base.size() - 1; i++)
	{
		vec3 joint1 = bones_base[i].locToGlobVec();
		vec3 joint2 = {};

		if (bones_base[i].parent)
			joint2 = bones_base[i].parent->locToGlobVec();

		DrawLine(joint1.x, joint1.y + offset, joint1.z,
				 joint2.x, joint2.y + offset, joint2.z,
				 0.f, 0.f, 1.f);
	}
}

void Skeleton::MoveBone(const int indexBone, const quat& rotation, const float& speed)
{
	if (indexBone < 0 || indexBone > bones.size())
		return;

	bones[indexBone].rot = quatSlerp(bones[indexBone].rot, bones[indexBone].rot * rotation, speed);
}

const float* Skeleton::GetBonesMatrix()
{
	float* matrix = new float[(bones.size()) * sizeof(Bone)];

	for (int i = 0; i < bones.size(); i++)
		memcpy(&matrix[i * (sizeof(mat4) / sizeof(float))], bones[i].GetMatrix(bones, bones_base).e, sizeof(mat4));

	return matrix;
}

const void Skeleton::animSkel(float& frameTime)
{
	quat currRotDiff = {};
	quat nextRotDiff = {};
	vec3 currPosDiff = {};
	vec3 nextPosDiff = {};

	static int currKeyFrame = 0;
	static float timer = 0.f;
	timer += frameTime;
	const static float timerBetweenFrame = 0.05f;
	const char* animName = "ThirdPersonWalk.anim";

	if (timer >= timerBetweenFrame)
	{
		++currKeyFrame;
		timer = 0.f;
	}

	float newTimer = timer / timerBetweenFrame;

	for (auto& bone : bones)
	{
		GetAnimLocalBoneTransform(animName, bone.index, currKeyFrame % GetAnimKeyCount(animName), currPosDiff.x, currPosDiff.y, currPosDiff.z, currRotDiff.w, currRotDiff.x, currRotDiff.y, currRotDiff.z);
		GetAnimLocalBoneTransform(animName, bone.index, (currKeyFrame + 1) % GetAnimKeyCount(animName), nextPosDiff.x, nextPosDiff.y, nextPosDiff.z, nextRotDiff.w, nextRotDiff.x, nextRotDiff.y, nextRotDiff.z);

		//bone->currAnimPos = matrixToPosition(bone->globalAnimModel);

		bone.pos = bones_base[bone.index].pos + lerp(currPosDiff, nextPosDiff, newTimer);
		bone.rot = bones_base[bone.index].rot * quatSlerp(currRotDiff, nextRotDiff, newTimer);

		//bone->localAnimModel = translate(bone->pos) * quaternionToMatrix(currRotDiff);
		//bone->globalAnimModel = bones_base[bone->index]->GetGlobalModel() * bone->localAnimModel;
		
		//if (bone->parent)
		//	bone->globalAnimModel = bone->parent->globalAnimModel * bone->globalAnimModel;
	}
}
#include "Animation.h"

#include "Engine.h"
#include "stdafx.h"

Animation::Animation()
{
	skel = &Skeleton();
}

// le nouveau nom du set
void Animation::Init()
{
	const char* animName = "ThirdPersonWalk.anim";
	static int currKeyFrame = 0;

	quat tempRot = {};
	vec3 tempPos = {};

	for (int i = 0; i < GetSkeletonBoneCount() - 7; i++) // - 7 to remove IK
	{
		GetAnimLocalBoneTransform(animName, i, currKeyFrame % GetAnimKeyCount(animName), tempPos.x, tempPos.y, tempPos.z, tempRot.w, tempRot.x, tempRot.y, tempRot.z);
		++currKeyFrame;
		localRotDiff.push_back(tempRot);
		localPosDiff.push_back(tempPos);
	}

	skel->Init();
}

void Animation::Update(float frameTime)
{
	//SetSkinningPose(skel->GetBonesMatrix(), size_t(skel->GetBonesNumber()));
	//skel->animSkel(frameTime);
}
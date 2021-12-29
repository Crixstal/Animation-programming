#include "Animation.h"

#include "Engine.h"
#include "stdafx.h"

Animation::Animation()
{
	skel = new Skeleton();
}

void Animation::Init()
{
	skel->Init();

	for (int i = 0; i < GetSkeletonBoneCount() - 7; i++) // - 7 to remove IK
	{
		Bone& currentBone = *skel->bones[i].get();
		GetAnimLocalBoneTransform(animName, i, i % GetAnimKeyCount(animName), currentBone.pos.x, currentBone.pos.y, currentBone.pos.z,
																	currentBone.rot.w, currentBone.rot.x, currentBone.rot.y, currentBone.rot.z);
	}
}

void Animation::Update(const float& frameTime)
{
	SetSkinningPose(skel->GetBonesMatrix(), size_t(skel->GetBonesNumber()));
	//skel->animSkel(frameTime, animName);
	skel->MoveBone(52, { 0.f, 1.f, 0.f, 0.f }, 0.0005f);
	skel->Draw();
}
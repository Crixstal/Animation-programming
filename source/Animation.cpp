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

	keyFrameNumber = GetAnimKeyCount(animName);

	for (int i = 0; i < keyFrameNumber; ++i)
	{
		animTransforms.push_back(std::vector<std::shared_ptr<Bone>>());
		
		for (int j = 0; j < skel->GetBonesNumber(); ++j)
		{
			animTransforms[i].push_back(std::make_shared<Bone>());

			animTransforms[i][j]->index = j;
			animTransforms[i][j]->name = GetSkeletonBoneName(j);

			if (GetSkeletonBoneParentIndex(j) == -1)
				animTransforms[i][j]->parent = nullptr;
			else
				animTransforms[i][j]->parent = animTransforms[i][GetSkeletonBoneParentIndex(j)].get();

			GetAnimLocalBoneTransform(animName, j, i, animTransforms[i][j]->pos.x, animTransforms[i][j]->pos.y, animTransforms[i][j]->pos.z,
						animTransforms[i][j]->rot.w, animTransforms[i][j]->rot.x, animTransforms[i][j]->rot.y, animTransforms[i][j]->rot.z);
		}
	}
}

void Animation::Update(const float& frameTime)
{
	timer += frameTime;

	if (timer >= timerBetweenFrame)
	{
		++currKeyFrame;
		timer = 0.f;
	}

	speed = timer / timerBetweenFrame;

	//skel->MoveBone(52, { 0.f, 1.f, 0.f, 0.f }, 100.f, 0.005f);
	skel->animSkel(speed, animTransforms[currKeyFrame % keyFrameNumber], animTransforms[(currKeyFrame + 1) % keyFrameNumber]);
	skel->Draw();
	SetSkinningPose(skel->GetBonesMatrix(animTransforms[currKeyFrame % keyFrameNumber]), size_t(skel->GetBonesNumber()));
}
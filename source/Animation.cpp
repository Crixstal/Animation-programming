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

	LoadAnimation();
}

void Animation::LoadAnimation()
{
	keyFrameNumber = GetAnimKeyCount(animName[currentAnimation]);

	//clear animTransforms
	animTransforms.clear();

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

			GetAnimLocalBoneTransform(animName[currentAnimation], j, i, animTransforms[i][j]->pos.x, animTransforms[i][j]->pos.y, animTransforms[i][j]->pos.z,
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
		if (currKeyFrame == GetAnimKeyCount(animName[currentAnimation]))
		{
			currKeyFrame = 0;
			
			if (currentAnimation == 0)
				currentAnimation = 1;
			else
				currentAnimation = 0;

			LoadAnimation();
		}
	}

	alpha = timer / timerBetweenFrame;

	// comment DrawWithAnim and uncomment Draw to see the skel in T-pose
	//skel->Draw();
	skel->DrawWithAnim(alpha, animTransforms[currKeyFrame % keyFrameNumber], animTransforms[(currKeyFrame + 1) % keyFrameNumber]);

	SetSkinningPose(skel->GetBonesMatrix(animTransforms[currKeyFrame % keyFrameNumber]), size_t(skel->GetBonesNumber()));
}
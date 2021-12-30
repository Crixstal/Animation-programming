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

	for (int i = 0; i < GetAnimKeyCount(animName); ++i)
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
	SetSkinningPose(skel->GetBonesMatrix(animTransforms), size_t(skel->GetBonesNumber()));
	//skel->animSkel(frameTime, animName);
	skel->MoveBone(1, { 0.f, 1.f, 0.f, 0.f }, 0.0005f);
	skel->Draw();
}
#include "Skeleton.h"

#include "Engine.h"

void Skeleton::Set()
{
	// Fill up bones

	Bone currentBone;

	// -7 is for don't get ik_ bones
	for (int i = 1; i < GetSkeletonBoneCount() - 7; i++)
	{
		currentBone.name = GetSkeletonBoneName(i);
		currentBone.index = i;

		GetSkeletonBoneLocalBindTransform(i, currentBone.pos[0], currentBone.pos[1], currentBone.pos[2],
					currentBone.quat[0], currentBone.quat[1], currentBone.quat[2], currentBone.quat[3]);

		bones.push_back(currentBone);
		
		printf("bone [%d] is named: %s\n", bones[i-1].index, bones[i-1].name);
	}
}

void Skeleton::Draw()
{
	for (int i = 0; i < bones.size() - 1; i++)
	{
		DrawLine(bones[i].pos[0], bones[i].pos[1] + offset, bones[i].pos[2],
				 bones[i + 1].pos[0], bones[i + 1].pos[1] + offset, bones[i + 1].pos[2],
				 0.f, 0.f, 1.f);	
	}
}
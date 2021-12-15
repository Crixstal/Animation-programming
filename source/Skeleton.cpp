#include "Skeleton.h"

#include "Engine.h"
#include "Referential.h"
#include "Quaternion.h"

void Skeleton::Set()
{
	Bone currentBone;

	for (int i = 0; i < GetSkeletonBoneCount() - 7; i++) // - 7 to remove IK
	{
		currentBone.name = GetSkeletonBoneName(i);
		currentBone.index = i;
		currentBone.parentIndex = GetSkeletonBoneParentIndex(i);

		GetSkeletonBoneLocalBindTransform(i, currentBone.pos[0], currentBone.pos[1], currentBone.pos[2],
					currentBone.quater[3], currentBone.quater[0], currentBone.quater[1], currentBone.quater[2]);

		bones.push_back(currentBone);
		
		printf("bone [%d] is named: %s\n", bones[i].index, bones[i].name);
	}
}

void Skeleton::Draw()
{
	for (int i = 2; i < bones.size() - 1; i++)
	{
		if (i == 0) // don't draw root to pelvis
			continue;

		vec3 test1 = bones[i].locToGlobBone(bones, bones[i].getVec(), 0);
		vec3 test2 = bones[bones[i].parentIndex].locToGlobBone(bones, bones[bones[i].parentIndex].getVec(), 0);

		DrawLine(test1.x, test1.y + offset, test1.z,
				 test2.x, test2.y + offset, test2.z,
				 0.f, 0.f, 1.f);	
	}
}

vec3 Bone::locToGlobBone(const std::vector<Bone>& bones, vec3 position, int deep)
{
	++deep;
	int parentID = index;
	for (int i = 0; i < deep; i++)
		parentID = bones[parentID].parentIndex;

	if (parentID != -1)
	{
		Referential refParent = { bones[parentID].getVec(), bones[parentID].getQuat() };
		
		vec3 posRelativeToParent = refParent.locToGlobPos(position);

		return locToGlobBone(bones, posRelativeToParent, deep);
	}

	return position;
}
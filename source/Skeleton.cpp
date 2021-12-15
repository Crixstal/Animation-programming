#include "Skeleton.h"

#include "Engine.h"
#include "stdafx.h"

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

		printf("bone %d name: %s\n", bones[i].index, bones[i].name);
	}
}

void Skeleton::Draw()
{
	for (int i = 2; i < bones.size() - 1; i++)
	{
		if (i == 0) // don't draw root to pelvis
			continue;

		vec3 joint1 = bones[i].locToGlobBone(bones, bones[i].getVec(), 0);
		vec3 joint2 = bones[bones[i].parentIndex].locToGlobBone(bones, bones[bones[i].parentIndex].getVec(), 0);

		DrawLine(joint1.x, joint1.y + offset, joint1.z,
				 joint2.x, joint2.y + offset, joint2.z,
				 0.f, 0.f, 1.f);
	}
}

void Skeleton::MoveBone(const int indexBone, const quat& rotation, const float& speed)
{
	if (indexBone < 0 || indexBone > bones.size())
		return;

	quat newQuat = quatSlerp(bones[indexBone].getQuat(), bones[indexBone].getQuat() * rotation, speed);
	bones[indexBone].quater[0] = newQuat.x;
	bones[indexBone].quater[1] = newQuat.y;
	bones[indexBone].quater[2] = newQuat.z;
	bones[indexBone].quater[3] = newQuat.w;
}

const float* Skeleton::GetBonesMatrix()
{
	float* matrix = new float[(bones.size()) * sizeof(Bone)];

	for (int i = 0; i < bones.size(); i++)
		memcpy(&matrix[i * (sizeof(mat4) / sizeof(float))], bones[i].GetMatrix(bones), sizeof(mat4));

	return matrix;
}
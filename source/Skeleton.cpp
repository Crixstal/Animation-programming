#include "Skeleton.h"

#include "Engine.h"
#include "Referential.h"
#include "Quaternion.h"
#include "Mat4.h"

#include <stdio.h>
#include <cstdlib>

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

void Skeleton::MoveBone(int indexBone, const quat& rotation, const float& speed)
{
	if (indexBone < 0 || indexBone > 60)
		return;

	quat newQuat = quatSlerp(bones[indexBone].getQuat(), bones[indexBone].getQuat() * rotation, speed);
	bones[indexBone].quater[0] = newQuat.x;
	bones[indexBone].quater[1] = newQuat.y;
	bones[indexBone].quater[2] = newQuat.z;
	bones[indexBone].quater[3] = newQuat.w;
}

const float* Skeleton::GetBonesMatrix()
{
	int numberOfbones = 60;

	const int matrixSize = numberOfbones * sizeof(Bone);
	float* matrix = new float[matrixSize];

	for (int i = 0; i < bones.size(); i++)
	{
		//vec3 globalPos = bones[i].locToGlobBone(bones, bones[i].getVec(), 0);
		//vec3 rot = quaternionToEuler(bones[i].getQuat());

		//mat4 T_moved = translate(globalPos);
		//mat4 R_moved = rotateX(rot.x) * rotateY(rot.y) * rotateZ(rot.z);
		//mat4 S_moved = scale({ 1.f, 1.f, 1.f });

		//mat4 TRS_moved = T_moved * R_moved * S_moved;

		////

		//Bone currentBone;
		//currentBone.name = GetSkeletonBoneName(i);
		//currentBone.index = i;
		//currentBone.parentIndex = GetSkeletonBoneParentIndex(i);
		//GetSkeletonBoneLocalBindTransform(i, currentBone.pos[0], currentBone.pos[1], currentBone.pos[2],
		//	currentBone.quater[3], currentBone.quater[0], currentBone.quater[1], currentBone.quater[2]);
		//
		//vec3 baseBonePos = currentBone.locToGlobBone(bones, currentBone.getVec(), 0);

		//rot = quaternionToEuler(currentBone.getQuat());

		//mat4 T = translate(baseBonePos);
		//mat4 R = rotateX(rot.x) * rotateY(rot.y) * rotateZ(rot.z);
		//mat4 S = scale({ 1.f, 1.f, 1.f });

		//mat4 TRS_base = T * R * S;
		//
		//// the (strange) matrix to return
		//mat4 to_return = TRS_moved * matInvert(TRS_base);

		//float to_return[16];
		//to_return = bones[i].GetMatrix(bones);

		memcpy(&matrix[i * 16], bones[i].GetMatrix(bones), sizeof(mat4));
	}

	return matrix;
}


float* Bone::GetMatrix(const std::vector<Bone>& bones)
{
	vec3 globalPos = locToGlobBone(bones, getVec(), 0);
	vec3 rot = quaternionToEuler(getQuat());

	mat4 T_moved = translate(globalPos);
	mat4 R_moved = rotateX(rot.x) * rotateY(rot.y) * rotateZ(rot.z);
	mat4 S_moved = scale({ 1.f, 1.f, 1.f });

	mat4 TRS_moved = T_moved * R_moved * S_moved;

	//

	Bone currentBone;
	currentBone.name = GetSkeletonBoneName(index);
	currentBone.index = index;
	currentBone.parentIndex = GetSkeletonBoneParentIndex(index);
	GetSkeletonBoneLocalBindTransform(index, currentBone.pos[0], currentBone.pos[1], currentBone.pos[2],
		currentBone.quater[3], currentBone.quater[0], currentBone.quater[1], currentBone.quater[2]);

	vec3 baseBonePos = currentBone.locToGlobBone(bones, currentBone.getVec(), 0);

	rot = quaternionToEuler(currentBone.getQuat());

	mat4 T = translate(baseBonePos);
	mat4 R = rotateX(rot.x) * rotateY(rot.y) * rotateZ(rot.z);
	mat4 S = scale({ 1.f, 1.f, 1.f });

	mat4 TRS_base = T * R * S;

	// the (strange) matrix to return
	mat4 to_return = TRS_moved * matInvert(TRS_base);

	float* realreturn = to_return.e;

	return realreturn;
}
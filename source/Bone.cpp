#include "Bone.h"

#include "Engine.h"
#include "stdafx.h"

vec3 Bone::locToGlobBone(const std::vector<Bone>& bones, const vec3& position, int deep)
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

float* Bone::GetMatrix(const std::vector<Bone>& bones)
{
	//Bone currentBone;
	//currentBone.name = GetSkeletonBoneName(index);
	//currentBone.index = index;
	//currentBone.parentIndex = GetSkeletonBoneParentIndex(index);
	//GetSkeletonBoneLocalBindTransform(index, currentBone.pos[0], currentBone.pos[1], currentBone.pos[2],
	//			currentBone.quater[3], currentBone.quater[0], currentBone.quater[1], currentBone.quater[2]);
	//vec3 baseBonePos = currentBone.locToGlobBone(bones, currentBone.getVec(), 0);

	//vec3 rot = quaternionToEuler(currentBone.getQuat());

	//mat4 T = translate(baseBonePos);
	mat4 T = translate(locToGlobBone(bones, getVec(), 0));
	//mat4 T = translate(getVec());
	//mat4 R = rotateXYZ(rot);
	mat4 R = rotateXYZ(quaternionToEuler(getQuat()));
	mat4 S = scale({ 1.f, 1.f, 1.f });

	mat4 TRS_base = T * R * S;


	vec3 globalPos = locToGlobBone(bones, getVec(), 0);

	mat4 T_moved = translate(globalPos);

	mat4 TRS_moved = T_moved * R * S;


	// the (strange) matrix to return
	mat4 to_return = TRS_moved * matInvert(TRS_base); // il manque pas TRS_base ?

	return to_return.e;
}
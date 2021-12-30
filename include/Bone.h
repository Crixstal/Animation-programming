#pragma once

#include <vector>
#include <memory>

#include "Definitions.h"
#include "Quaternion.h" // include Mat4.h which include Vector3.h

class Bone
{
public:
	Bone() {}
	~Bone() {}

	const char* name = nullptr;
	int index = 0;
	Bone* parent = nullptr;
	vec3 pos = {};
	quat rot = quatIdentity();

	mat4 globalAnimModel = matIdentity();

	vec3 locToGlobVec(const vec3& myVec) const;
	quat locToGlobQuat(const quat& myQuat) const;

	mat4 GetMatrix(const std::vector<std::vector<std::shared_ptr<Bone>>>& animTransforms, const std::vector<std::shared_ptr<Bone>>& bones_base);
	mat4 GetLocalModel() const;
	mat4 GetGlobalModel() const;
};
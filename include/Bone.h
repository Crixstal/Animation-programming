#pragma once

#include <vector>
#include <memory>

#include "Definitions.h"

class Bone
{
public:
	Bone() {}
	~Bone() {}

	const char* name = nullptr;
	int index = 0;
	Bone* parent = nullptr;
	vec3 pos = {};
	quat rot = {};

	// truc de gros sale
	mat4 localAnimModel = {};
	mat4 globalAnimModel = {};
	vec3 currAnimPos = {};
	quat currAnimRot = {};

	vec3 locToGlobVec(const vec3& myVec) const;
	quat locToGlobQuat(const quat& myQuat) const;

	mat4 GetMatrix(const std::vector<std::shared_ptr<Bone>>& bones, const std::vector<std::shared_ptr<Bone>>& bones_base);
	mat4 GetLocalModel() const;
	mat4 GetGlobalModel() const;
};
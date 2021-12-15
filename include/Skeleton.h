#pragma once

#include <vector>
#include "Definitions.h"

class Bone
{
public:
	const char* name = nullptr;
	int index = 0;
	int parentIndex = 0;
	float pos[3] = {};
	float quater[4] = {};

	vec3 locToGlobBone(const std::vector<Bone>& bones, vec3 position, int deep);

	vec3 getVec() const { return vec3(pos[0], pos[1], pos[2]); };
	quat getQuat() const { return quat(quater[0], quater[1], quater[2], quater[3]); };
};

class Skeleton
{
public:
	Skeleton() {}
	~Skeleton() {}

	void Set();
	void Draw();

private:
	std::vector<Bone> bones;
	float offset = -100.f;
};
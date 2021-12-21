#pragma once

#include <vector>

#include "Bone.h"
#include "Definitions.h"

class Animation
{
public:
	Animation() {}
	~Animation() {}

	//Skeleton* skel = nullptr;
	std::vector<quat> localRotDiff;
	std::vector<vec3> localPosDiff;
	//quat localRotDiff = {};
	//vec3 localPosDiff = {};

	void Set();
};
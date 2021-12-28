#pragma once

#include <vector>

#include "Bone.h"
#include "Definitions.h"

class Skeleton;

class Animation
{
public:
	Animation();
	~Animation() {};
	
	void Update(float frameTime);

	// Skeleton to animate
	Skeleton* skel = nullptr;

	//	Local differences
	std::vector<quat> localRotDiff;
	std::vector<vec3> localPosDiff;

	//	Animation matrix data
	std::vector<mat4> TRSLocalAnim;
	std::vector<mat4> TRSGlobalAnim;

	void Init();
};
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

	void Init();
	void Update(const float& frameTime);
	
private:
	const char* animName = "ThirdPersonWalk.anim";
	Skeleton* skel = nullptr;
};
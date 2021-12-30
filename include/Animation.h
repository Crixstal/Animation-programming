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

	std::vector<std::vector<std::shared_ptr<Bone>>> animTransforms;

private:
	const char* animName = "ThirdPersonWalk.anim";
	Skeleton* skel = nullptr;
};
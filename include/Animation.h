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

	void LoadAnimation();

private:
	std::vector<std::vector<std::shared_ptr<Bone>>> animTransforms;
	unsigned int keyFrameNumber = 0;
	int currKeyFrame = 0;
	float timer = 0.f;
	const float timerBetweenFrame = 0.0375f;
	float alpha = 0.f;

	int currentAnimation = 0;
	const char* animName[2] = { "ThirdPersonWalk.anim", "ThirdPersonRun.anim" };
	Skeleton* skel = nullptr;
};
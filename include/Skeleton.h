#pragma once

#include <vector>

class Bone
{
public:
	const char* name;
	int index;
	float pos[3];
	float quat[4];
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
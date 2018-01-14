#pragma once
#include "Cube3d.h"
class TargetCube
	: public Cube3d
{
public:
	TargetCube(float x, float y, float z, float width, float height, float depth);
	~TargetCube();

	virtual void Update(float deltaTime) override;
};


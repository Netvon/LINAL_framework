#include "TargetCube.h"


TargetCube::TargetCube(float x, float y, float z, float width, float height, float depth)
	: Cube3d(x, y, z, width, height, depth)
{
}

TargetCube::~TargetCube()
{
}

void TargetCube::Update(float deltaTime)
{
	if (scale_x() <= 1.f) {
		scale_x() += 0.1f * deltaTime;
		scale_y() += 0.1f * deltaTime;
		scale_x() += 0.1f * deltaTime;
	}
	else if( scale_x() >= 2.f) {
		scale_x() -= 0.1f * deltaTime;
		scale_y() -= 0.1f * deltaTime;
		scale_x() -= 0.1f * deltaTime;
	}
}

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
	constexpr float pulse_speed = 1.5f;
	constexpr float pulse_max = 1.5f;
	constexpr float pulse_min = 0.5f;

	if (scale_up) {
		scale_x() += pulse_speed * deltaTime;
		scale_y() += pulse_speed * deltaTime;
		scale_z() += pulse_speed * deltaTime;
	}
	else {
		scale_x() -= pulse_speed * deltaTime;
		scale_y() -= pulse_speed * deltaTime;
		scale_z() -= pulse_speed * deltaTime;
	}

	if (scale_x() >= pulse_max) {
		scale_up = false;
	}
	else if (scale_x() <= pulse_min) {
		scale_up = true;
	}

	_rotate += 1.f * deltaTime;
	if (_rotate > 360.f)
		_rotate = 0.f;

	roll() += 10.f * deltaTime;

	_needs_update = true;
}

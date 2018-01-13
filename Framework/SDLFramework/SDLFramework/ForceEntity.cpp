#include "ForceEntity.h"

const Vec3 & ForceEntity::location() const
{
	return _location;
}

const Vec3 & ForceEntity::velocity() const
{
	return _velocity;
}

float ForceEntity::movement_speed() const
{
	return _movement_speed;
}

void ForceEntity::movement_speed(float new_value)
{
	_movement_speed = new_value;
}

void ForceEntity::update_location(float deltaTime)
{
	_location += ( ( _velocity.normalize() * _movement_speed ) * deltaTime );

	int loc_x = static_cast<int>(_location.x());
	int loc_y = static_cast<int>(_location.y());

	SetOffset(loc_x, loc_y);
}

void ForceEntity::Update(float deltaTime)
{
	if (!mIsActive) {
		return;
	}
	else {
		additional_update(deltaTime);
		
		if (!mIsActive) return;
	}

	update_location(deltaTime);
}

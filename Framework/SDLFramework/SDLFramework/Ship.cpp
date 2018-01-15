#include "Ship.h"


Ship::Ship(float x, float y, float z, float width, float height, float depth)
	: Cube3d(x, y, z, width, height, depth)
{

	add_point({ 0.f, -2.f, 0.f, 1.f });

	add_line({ 8llu, 4llu });
	add_line({ 8llu, 5llu });
	add_line({ 8llu, 3llu });
	add_line({ 8llu, 2llu });
}

Ship::~Ship()
{
}

void Ship::Update(float deltaTime)
{
	_velocity = up() * _speed * deltaTime;

	x() += _velocity.x();
	y() += _velocity.y();
	z() += _velocity.z();

	if(_speed > 0.f)
		_speed -= 30.f * deltaTime;
	else if (_speed < 0.f)
		_speed += 30.f * deltaTime;
}

float & Ship::speed()
{
	return _speed;
}

const Vec3 & Ship::velocity() const
{
	return _velocity;
}

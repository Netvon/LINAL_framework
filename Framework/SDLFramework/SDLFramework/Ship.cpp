#include "Ship.h"


Ship::Ship(float x, float y, float z, float width, float height, float depth)
	: Cube3d(x, y, z, width, height, depth)
{

	add_point({ 0.f, -2.f, 0.f, 1.f });
	add_point({ -3.f, 0.f, 0.f, 1.f });
	add_point({ 3.f, 0.f, 0.f, 1.f });
	add_point({ 0.f, -1.f, 0.f, 1.f });

	add_line({ 8llu, 4llu });
	add_line({ 8llu, 5llu });
	add_line({ 8llu, 3llu });
	add_line({ 8llu, 2llu });
	add_line({ 10llu, 9llu });
	add_line({ 11lu, 10llu });
	add_line({ 11llu, 9llu });
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
		_speed -= _dampening * deltaTime;
	else if (_speed < 0.f)
		_speed += _dampening * deltaTime;

	Vec3 roll{ 0.f, 1.f, 0.f };
	Vec3 dive{ 1.f, 0.f, 0.f };
	Vec3 rotation_axis{ 0.f, 0.f, 1.f };

	reset_rotate();
	rotate(rotation_axis, _turn);
	rotate(roll, _roll);
	rotate(dive, _dive);
}

float & Ship::roll()
{
	return _roll;
}

float & Ship::dive()
{
	return _dive;
}

float & Ship::speed()
{
	return _speed;
}

float & Ship::dampening()
{
	return _dampening;
}

float & Ship::turn()
{
	return _turn;
}

const Vec3 & Ship::velocity() const
{
	return _velocity;
}

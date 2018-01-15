#include "Cube3d.h"

Cube3d::Cube3d(float x, float y, float z, float width, float height, float depth)
	: Object(x, y, z, width, height, depth)
{
	add_point({ 1.f, 1.f, 1.f, 1.f });
	add_point({ -1.f, 1.f, 1.f, 1.f });
	add_point({ -1.f, -1.f, 1.f, 1.f });
	add_point({ 1.f, -1.f, 1.f, 1.f });

	add_point({ 1.f, 1.f, 1.f, -1.f });
	add_point({ -1.f, 1.f, 1.f, -1.f });
	add_point({ -1.f, -1.f, 1.f, -1.f });
	add_point({ 1.f, -1.f, 1.f, -1.f });


	line_draw_order = {
		{ 0llu, 1llu },
		{ 0llu, 6llu },
		{ 3llu, 0llu },
		{ 3llu, 5llu },
		{ 3llu, 2llu },
		{ 2llu, 4llu },
		{ 4llu, 5llu },
		{ 4llu, 7llu },
		{ 2llu, 1llu },
		{ 7llu, 1llu },
		{ 6llu, 7llu },
		{ 6llu, 5llu },
	};
}


void Cube3d::Update(float deltaTime)
{
	if (_speed == 0.f && !(_turn != 0.f || _roll != 0.f || _dive != 0.f)) {
		_needs_update = false;
		_velocity = { 0.0f, 0.0f, 0.0f };
		return;
	}

	if (_speed > _vmax)
		_speed = _vmax;
	else if (_speed < -_vmax)
		_speed = -_vmax;

	_velocity = _heading * _speed * deltaTime;

	x() += _velocity.x();
	y() += _velocity.y();
	z() += _velocity.z();

	if (_speed > 0.f)
		_speed -= _dampening * deltaTime;
	else if (_speed < 0.f)
		_speed += _dampening * deltaTime;
	
	if (_speed > 0.f && _speed <= 0.09f) {
		_speed = 0.f;
		_velocity = { 0.0f, 0.0f, 0.0f };
		return;
	}

	reset_rotate();
	rotate(rotation_axis, _turn);
	rotate(roll_axis, _roll);
	rotate(dive_axis, _dive);
	_needs_update = true;
}

float & Cube3d::roll()
{
	return _roll;
}

float & Cube3d::dive()
{
	return _dive;
}

float & Cube3d::speed()
{
	return _speed;
}

float & Cube3d::dampening()
{
	return _dampening;
}

float & Cube3d::turn()
{
	return _turn;
}

float & Cube3d::vmax()
{
	return _vmax;
}

Vec & Cube3d::heading()
{
	return _heading;
}

const Vec3 & Cube3d::velocity() const
{
	return _velocity;
}

void Cube3d::is_active(bool value)
{
	_needs_update = value;
}



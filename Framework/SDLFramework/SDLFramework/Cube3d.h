#pragma once

#include "Object.h"

class Cube3d
	: public Object
{
public:

	Cube3d(float x, float y, float z, float width, float height, float depth);

	float& roll();
	float& dive();
	float& speed();
	float& dampening();
	float& turn();
	const Vec3& velocity() const;

	// Inherited via Object
	virtual void Update(float deltaTime) override;
private:
	float _speed{ 0.f };
	float _roll{ 0.f };
	float _dive{ 0.f };
	float _dampening{ 30.f };
	float _turn{ 0.f };
	Vec3 _velocity{ 0.f, 0.f, 0.f };
};

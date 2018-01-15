#pragma once
#include "Cube3d.h"
class Ship 
	: public Cube3d
{
public:
	Ship(float x, float y, float z, float width, float height, float depth);
	~Ship();

	virtual void Update(float deltaTime) override;

	float& roll();
	float& dive();
	float& speed();
	float& dampening();
	float& turn();
	const Vec3& velocity() const;

private:

	float _speed{ 0.f };
	float _roll{ 0.f };
	float _dive{ 0.f };
	float _dampening{ 30.f };
	float _turn{ 0.f };
	Vec3 _velocity{ 0.f, 0.f, 0.f };
};


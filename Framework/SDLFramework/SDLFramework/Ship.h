#pragma once
#include "Cube3d.h"
class Ship 
	: public Cube3d
{
public:
	Ship(float x, float y, float z, float width, float height, float depth);
	~Ship();

	virtual void Update(float deltaTime) override;

	float& speed();

private:

	float _speed = 0.0f;
};


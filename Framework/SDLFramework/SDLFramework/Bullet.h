#pragma once

#include "Object.h"

class Bullet :
	public Object
{
public:
	Bullet(float x, float y, float z, float width, float height, float depth);
	~Bullet();

	// Inherited via Object
	virtual void Update(float deltaTime) override;
};


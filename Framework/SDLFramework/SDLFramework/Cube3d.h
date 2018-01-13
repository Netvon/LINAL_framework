#pragma once

#include "Shape.h"
#include "IGameObject.h"

class Cube3d
	: public Shape, public IGameObject
{
public:
	Cube3d(float x, float y, float z, float width, float height, float depth);

	float& x();
	float& y();
	float& z();

	float& width();
	float& height();
	float& depth();

	float& scale_x();
	float& scale_y();
	float& scale_z();

	float& rotation();

	// Inherited via IGameObject
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	void draw_line(Vec & last, Vec & current);

	void update_rotation();

	float _rotation = 0.0f;
};

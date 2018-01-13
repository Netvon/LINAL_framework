#pragma once
#include "Shape.h"
#include "IGameObject.h"

class Square2d 
	: public Shape, public IGameObject
{
public:
	Square2d(float x, float y, float width, float height);

	float& x();
	float& y();

	float& width();
	float& height();

	float& scale_x();
	float& scale_y();

	float& rotation();

	// Inherited via IGameObject
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	void draw_line(Vec & last, Vec & current);

	void update_rotation();

	float _rotation = 0.0f;
};

#pragma once

#include "Shape.h"
#include "IGameObject.h"

class Cube3d
	: public Shape, public IGameObject
{
public:

	struct line {
		size_t a, b;
	};

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

	Matrix rendered_points() const;

private:
	void draw_rect(const Vec& current) const;
	void draw_line(const Vec& last, const Vec& current) const;

	void update_rotation();

	float _rotation = 0.0f;

	Matrix _rendered;

	std::vector<line> line_draw_order;
};

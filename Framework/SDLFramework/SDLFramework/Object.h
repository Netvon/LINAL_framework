#pragma once

#include "Shape.h"
#include "IGameObject.h"

class Object
	: public Shape, public IGameObject
{
public:

	struct line {
		size_t a, b;
	};

	Object(float x, float y, float z, float width, float height, float depth);

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

	const Color& line_color() const;
	void line_color(const Color& line_color);


protected:
	std::vector<line> line_draw_order;

private:
	void draw_center(const Vec& current) const;
	void draw_rect(const Vec& current) const;
	void draw_line(const Vec& last, const Vec& current) const;

	void update_rotation();

	float _rotation = 0.0f;

	Matrix _rendered;
	Color _line_color{ 80, 80, 80, 255 };
};

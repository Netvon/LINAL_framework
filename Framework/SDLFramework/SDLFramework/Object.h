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

	float& local_x();
	float& local_y();
	float& local_z();

	float& width();
	float& height();
	float& depth();

	float& scale_x();
	float& scale_y();
	float& scale_z();

	float& rotation();

	// Inherited via IGameObject
	virtual void Update(float deltaTime) override = 0;
	virtual void Draw() override;

	Matrix rendered_points() const;

	const Color& line_color() const;
	void line_color(const Color& line_color);

	void rotate(const Vec3& around, float angle);


protected:
	std::vector<line> line_draw_order;

private:
	void draw_center(const Vec& current) const;
	void draw_rect(const Vec& current) const;
	void draw_line(const Vec& last, const Vec& current) const;

	float _rot = 360.0f;
	Vec3 _v{ 0.f, 0.f, 0.f };
	Matrix _rotation;

	Matrix _rendered;
	Color _line_color{ 80, 80, 80, 255 };
};

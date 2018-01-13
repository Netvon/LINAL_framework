#include "Cube3d.h"

Cube3d::Cube3d(float x, float y, float z, float width, float height, float depth)
{
	add_point({ 1.f, 1.f, 1.f, 1.f });
	add_point({ -1.f, 1.f, 1.f, 1.f });
	add_point({ -1.f, -1.f, 1.f, 1.f });
	add_point({ 1.f, -1.f, 1.f, 1.f });

	add_point({ 1.f, 1.f, 1.f, -1.f });
	add_point({ -1.f, 1.f, 1.f, -1.f });
	add_point({ -1.f, -1.f, 1.f, -1.f });
	add_point({ 1.f, -1.f, 1.f, -1.f });

	Matrix translate(4, 4, true); translate.name("translate");
	Matrix size(4, 4, true); size.name("size");
	Matrix scale(4, 4, true); scale.name("scale");

	add_transform(translate);
	add_transform(size);
	add_transform(scale);

	this->x() = x;
	this->y() = y;
	this->z() = z;

	this->width() = width;
	this->height() = height;
	this->depth() = depth;


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

float & Cube3d::x()
{
	auto& me = (*this);

	return me("translate")(0, 3);
}

float & Cube3d::y()
{
	auto& me = (*this);

	return me("translate")(1, 3);
}

float & Cube3d::z()
{
	auto& me = (*this);

	return me("translate")(2, 3);
}

float & Cube3d::width()
{
	auto& me = (*this);

	return me("size")(0, 0);
}

float & Cube3d::height()
{
	auto& me = (*this);

	return me("size")(1, 1);
}

float & Cube3d::depth()
{
	auto& me = (*this);

	return me("size")(2, 2);
}

float & Cube3d::scale_x()
{
	auto& me = (*this);

	return me("scale")(0, 0);
}

float & Cube3d::scale_y()
{
	auto& me = (*this);

	return me("scale")(1, 1);
}

float & Cube3d::scale_z()
{
	auto& me = (*this);

	return me("scale")(2, 2);
}

void Cube3d::Update(float deltaTime)
{
}

void Cube3d::Draw()
{
	Camera& camera = mApplication->GetCamera();
	Matrix output = camera.fix(camera.matrix() * transform());

	for (auto& rect : output) {
		draw_rect(rect);
	}

	for (auto& line : line_draw_order) {
		draw_line(output[line.a], output[line.b]);
	}

	
}

void Cube3d::draw_rect(const Vec & current) const
{
	constexpr int point_size = 5;
	constexpr int half_point_size = point_size / 2;

	int end_x = static_cast<int>(std::round(current[0]));
	int end_y = static_cast<int>(std::round(current[1]));

	mApplication->SetColor(Color(204, 141, 16, 128));
	mApplication->DrawRect(end_x - half_point_size, end_y - half_point_size, point_size, point_size, true);
}

void Cube3d::draw_line(const Vec& last, const Vec& current) const
{
	constexpr int point_size = 5;
	constexpr int half_point_size = point_size / 2;

	int start_x = static_cast<int>(std::round(last[0]));
	int start_y = static_cast<int>(std::round(last[1]));

	int end_x = static_cast<int>(std::round(current[0]));
	int end_y = static_cast<int>(std::round(current[1]));

	mApplication->SetColor(Color(80, 80, 80, 255));
	mApplication->DrawLine(start_x, start_y, end_x, end_y);
}

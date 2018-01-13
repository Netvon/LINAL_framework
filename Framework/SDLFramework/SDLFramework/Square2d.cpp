#include "Square2d.h"

Square2d::Square2d(float x, float y, float width, float height)
{	
	add_point({ 1.f, 1.f, 1.f });
	add_point({ -1.f, 1.f, 1.f });
	add_point({ -1.f, -1.f, 1.f });
	add_point({ 1.f, -1.f, 1.f });

	Matrix translate( 3, 3, true ); translate.name("translate");
	Matrix size( 3, 3, true ); size.name("size");
	Matrix scale( 3, 3, true ); scale.name("scale");
	Matrix rotate(3, 3, true); rotate.name("rotate");

	add_transform(translate);
	add_transform(rotate);
	add_transform(size);
	add_transform(scale);

	this->x() = x;
	this->y() = y;

	this->width() = width;
	this->height() = height;
}

float & Square2d::x()
{
	auto& me = (*this);

	return me("translate")(0, 2);
}

float & Square2d::y()
{
	auto& me = (*this);

	return me("translate")(1, 2);
}

float & Square2d::width()
{
	auto& me = (*this);

	return me("size")(0, 0);
}

float & Square2d::height()
{
	auto& me = (*this);

	return me("size")(1, 1);
}

float & Square2d::scale_x()
{
	auto& me = (*this);

	return me("scale")(0, 0);
}

float & Square2d::scale_y()
{
	auto& me = (*this);

	return me("scale")(1, 1);
}

float & Square2d::rotation()
{
	return _rotation;
}

void Square2d::Update(float deltaTime)
{
	_rotation += 50.f * deltaTime;

	x() += 40.f * deltaTime;
	if (x() > 400.f) {
		x() = 0.f;
	}

	if(scale_x() < 2.f)
		scale_x() += 0.5f * deltaTime;
	else if (scale_y() < 2.f)
		scale_y() += 0.5f * deltaTime;

	update_rotation();
}

void Square2d::Draw()
{
	Matrix output = transform();

	Vec last = output[0];

	for (size_t i = 1; i < output.columns(); i++)
	{
		Vec& current = output[i];
		draw_line(last, current);
		last = current;
	}

	draw_line(last, output[0]);
}

void Square2d::draw_line(Vec & last, Vec & current)
{
	constexpr int point_size = 5;
	constexpr int half_point_size = point_size / 2;

	int start_x = static_cast<int>(std::round(last[0]));
	int start_y = static_cast<int>(std::round(last[1]));

	int end_x = static_cast<int>(std::round(current[0]));
	int end_y = static_cast<int>(std::round(current[1]));

	mApplication->SetColor(Color(255, 255, 255, 255));
	mApplication->DrawLine(start_x, start_y, end_x, end_y);

	mApplication->SetColor(Color(0, 0, 0, 32));
	mApplication->DrawRect(start_x - half_point_size, start_y - half_point_size, point_size, point_size, true);
	mApplication->DrawRect(end_x - half_point_size, end_y - half_point_size, point_size, point_size, true);
}

void Square2d::update_rotation()
{
	constexpr float convert = 3.141592654f / 180.f;
	float rad = convert * _rotation;

	auto& me = (*this);
	auto& rot = me("rotate");

	rot(0, 0) = cos(rad);
	rot(0, 1) = sin(rad);
	rot(0, 2) = 0.f;
			
	rot(1, 0) = -sin(rad);
	rot(1, 1) = cos(rad);
	rot(1, 2) = 0.f;
			
	rot(2, 0) = 0.f;
	rot(2, 1) = 0.f;
	rot(2, 2) = 1.f;
}

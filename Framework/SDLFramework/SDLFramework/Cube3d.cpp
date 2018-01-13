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

	Vec last = output[0];

	for (size_t i = 1; i < output.columns(); i++)
	{
		Vec& current = output[i];
		draw_line(last, current);
		last = current;
	}

	draw_line(last, output[0]);
}

void Cube3d::draw_line(Vec & last, Vec & current)
{
	if (last.zero() || current.zero()) {
		return;
	}

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

#include "Object.h"
#include "RandomGenerator.h"

Object::Object(const Object & other)
	: Shape(other), line_draw_order{ other.line_draw_order }
{
}

Object::Object(float x, float y, float z, float width, float height, float depth)
{
	Matrix translate(4, 4, true); translate.name("translate");
	Matrix local_translate(4, 4, true); local_translate.name("local_translate");
	Matrix size(4, 4, true); size.name("size");
	Matrix scale(4, 4, true); scale.name("scale");
	Matrix rotate(4, 4, true); rotate.name("rotate");

	add_transform(translate);
	add_transform(rotate);
	add_transform(local_translate);
	add_transform(size);
	add_transform(scale);

	this->x() = x;
	this->y() = y;
	this->z() = z;

	this->width() = width;
	this->height() = height;
	this->depth() = depth;
}

float & Object::x()
{
	auto& me = (*this);

	return me("translate")(0, 3);
}

float & Object::y()
{
	auto& me = (*this);

	return me("translate")(1, 3);
}

float & Object::z()
{
	auto& me = (*this);

	return me("translate")(2, 3);
}

float & Object::local_x()
{
	auto& me = (*this);
	return me("local_translate")(0, 3);
}

float & Object::local_y()
{
	auto& me = (*this);
	return me("local_translate")(1, 3);
}


float & Object::local_z()
{
	auto& me = (*this);
	return me("local_translate")(2, 3);
}

float & Object::width()
{
	auto& me = (*this);

	return me("size")(0, 0);
}

float & Object::height()
{
	auto& me = (*this);

	return me("size")(1, 1);
}

float & Object::depth()
{
	auto& me = (*this);

	return me("size")(2, 2);
}

float & Object::scale_x()
{
	auto& me = (*this);

	return me("scale")(0, 0);
}

float & Object::scale_y()
{
	auto& me = (*this);

	return me("scale")(1, 1);
}

float & Object::scale_z()
{
	auto& me = (*this);

	return me("scale")(2, 2);
}

void Object::Draw()
{
	if (!_visible)
		return;

	Camera& camera = mApplication->GetCamera();
	Matrix output = camera.fix(camera.matrix() * transform());

	
	Matrix render_center = camera.fix(camera.matrix() * transform(Vec{ 0.0f, 0.0f, 0.0f, 1.0f }));
	draw_center(render_center[0]);


	for (auto& rect : output) {
		if (rect[1] < 0.f)
			continue;

		draw_rect(rect);
	}

	for (auto& line : line_draw_order) {
		Vec& a = output[line.a];
		Vec& b = output[line.b];

		if (a[1] < 0.f || b[1] < 0.f)
			continue;

		draw_line(a, b);
	}

	_rendered = output;
}

Matrix Object::rendered_points() const
{
	return _rendered;
}

const Color & Object::line_color() const
{
	return _line_color;
}

void Object::line_color(const Color & line_color)
{
	_line_color = line_color;
}

void Object::reset_rotate()
{
	(*this)("rotate") = Matrix(4, 4, true);
}

void Object::rotate(const Vec3 & around, float angle)
{
	if (angle == 0.f)
		return;

	float a = angle * (M_PI / 180.f);
	float t1 = atan2f(around.z(), around.x());
	float t2 = atan2f(around.y(), sqrt(around.x() * around.x() + around.z() * around.z()));

	/*float _x = x();
	float _y = y();
	float _z = z();*/

	/*_z += 20.f;
	_y += 20.f;
	_x += 20.f;*/

	/*Matrix mat0{
		{ 1.f, 0.f, 0.f, 0.f - _x },
		{ 0.f, 1.f, 0.f, 0.f - _y },
		{ 0.f, 0.f, 1.f, 0.f - _z },
		{ 0.f, 0.f, 0.f, 1.f },
	};*/

	Matrix mat1{
		{ cos(t1) , 0.f, sin(t1) , 0.f },
		{ 0.f     , 1.f, 0.f     , 0.f },
		{ -sin(t1), 0.f, cos(t1) , 0.f },
		{ 0.f     , 0.f, 0.f     , 1.f },
	};

	Matrix mat2{
		{ cos(t2) , sin(t2), 0.f, 0.f },
		{ -sin(t2), cos(t2), 0.f, 0.f },
		{ 0.f     , 0.f    , 1.f, 0.f },
		{ 0.f     , 0.f    , 0.f, 1.f },
	};

	Matrix mat3{
		{ 1.f, 0.f, 0.f, 0.f },
		{ 0.f, cos(a), -sin(a), 0.f },
		{ 0.f, sin(a), cos(a), 0.f },
		{ 0.f, 0.f, 0.f, 1.f },
	};

	Matrix mat4{
		{ cos(t2), -sin(t2), 0.f, 0.f },
		{ sin(t2), cos(t2), 0.f, 0.f },
		{ 0.f, 0.f, 1.f, 0.f },
		{ 0.f, 0.f, 0.f, 1.f },
	};

	Matrix mat5{
		{ cos(t1), 0.f, -sin(t1), 0.f },
		{ 0.f, 1.f, 0.f, 0.f },
		{ sin(t1), 0.f, cos(t1), 0.f },
		{ 0.f, 0.f, 0.f, 1.f },
	};

	/*Matrix mat6{
		{ 1.f, 0.f, 0.f, _x },
		{ 0.f, 1.f, 0.f, _y },
		{ 0.f, 0.f, 1.f, _y },
		{ 0.f, 0.f, 0.f, 1.f },
	};*/

	//(*this)("rotate") = mat0 * mat1 * mat2 * mat3 * mat4 * mat5 * mat6;
	(*this)("rotate") = (*this)("rotate") * ( /*mat6 **/ (mat5 * (mat4 * (mat3 * (mat2 * (mat1 /** mat0*/))))));
}

void Object::add_line(const Object::line & line)
{
	line_draw_order.push_back(line);
}

bool & Object::visible()
{
	return _visible;
}

void Object::draw_center(const Vec & current) const
{
	constexpr int point_size = 5;
	constexpr int half_point_size = point_size / 2;

	int end_x = static_cast<int>(std::round(current[0]));
	int end_y = static_cast<int>(std::round(current[1]));

	mApplication->SetColor(Color(14, 142, 108, 128));
	mApplication->DrawRect(end_x - half_point_size, end_y - half_point_size, point_size, point_size, true);
}

void Object::draw_rect(const Vec & current) const
{
	constexpr int point_size = 5;
	constexpr int half_point_size = point_size / 2;

	int end_x = static_cast<int>(std::round(current[0]));
	int end_y = static_cast<int>(std::round(current[1]));

	mApplication->SetColor(Color(204, 141, 16, 128));
	mApplication->DrawRect(end_x - half_point_size, end_y - half_point_size, point_size, point_size, true);

	if (mApplication->IsShowDebug()) {
		mApplication->DrawText(std::to_string(end_x) + "," + std::to_string(end_y), end_x, end_y, Color(9, 81, 226, 32));
	}
}

void Object::draw_line(const Vec& last, const Vec& current) const
{
	constexpr int point_size = 5;
	constexpr int half_point_size = point_size / 2;

	int start_x = static_cast<int>(std::round(last[0]));
	int start_y = static_cast<int>(std::round(last[1]));

	int end_x = static_cast<int>(std::round(current[0]));
	int end_y = static_cast<int>(std::round(current[1]));

	mApplication->SetColor(_line_color);
	mApplication->DrawLine(start_x, start_y, end_x, end_y);
}

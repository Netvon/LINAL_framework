#include "Camera.h"

Camera::Camera()
{
}

Vec & Camera::eye()
{
	return _eye;
}

Vec & Camera::look_at()
{
	return _look_at;
}

Vec & Camera::up()
{
	return _up;
}

float & Camera::far()
{
	return _far;
}

float & Camera::near()
{
	return _near;
}

float & Camera::fov()
{
	return _fov;
}

float & Camera::size()
{
	return _size;
}

Matrix Camera::matrix() const
{
	Vec4 _eye4 = _eye;
	Vec4 z = _eye - _look_at;
	z = z.normalize();

	Vec4 y = _up.normalize();
	Vec4 x = y.cross(z);
	x = x.normalize();

	y = z.cross(x);
	y = y.normalize();

	Matrix camera{
		{ x.x(), x.y(), x.z(), -(x.dot(_eye4)) },
		{ y.x(), y.y(), y.z(), -(y.dot(_eye4)) },
		{ z.x(), z.y(), z.z(), -(z.dot(_eye4)) },
		{ 0.f, 0.f, 0.f, 1.f }
	};

	constexpr float convert = 3.141592654f / 180.f;
	float a = _fov * convert;
	float scale = _near * tan(a * 0.5f);

	Matrix projection{
		{ scale, 0.0f, 0.0f, 0.0f },
		{ 0.0f, scale, 0.0f, 0.0f },
		{ 0.0f, 0.0f, (-_far) / (_far - _near), -1.f },
		{ 0.0f, 0.0f, ((-_far) * _near) / (_far - _near), 0.0f },
	};

	return projection * camera;
}

Matrix Camera::fix(const Matrix & from) const
{
	Matrix temp(from.columns(), from.rows());

	size_t index = 0;

	for (const Vec& vec : from) {
		Vec4 vector(vec);

		float x = (_size / 2.f) + (((vector.x() + 1.f) / vector.w()) * (_size * 0.5f));
		float y = (_size / 2.f) + (((vector.y() + 1.f) / vector.w()) * (_size * 0.5f));
		float z = -vector.z();

		temp[index] = Vec({ x, y, z, vector.w() });
		index++;
	}

	return temp;
}

#pragma once
#include "Vector.h"
#include "Matrix.h"

class Camera {
public:

	Camera();

	Vec& eye();
	Vec& look_at();
	Vec& up();

	float& far();
	float& near();
	float& fov();
	float& size();

	Matrix matrix() const;

	Matrix fix(const Matrix& from) const;

private:

	Vec _eye{ 0.f, 1.f, 0.f, 1.f };
	Vec _look_at{ 0.f, 1.f, 0.f, 1.f };
	Vec _up{ 0.f, 1.f, 0.f, 1.f };

	float _far;
	float _near;
	float _fov;
	float _size;
};
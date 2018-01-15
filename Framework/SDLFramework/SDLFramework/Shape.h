#pragma once
#include "Vector.h"
#include "Matrix.h"
#include <initializer_list>
#include <algorithm>
#include <numeric>
#include <stdexcept>

class Shape
	: public Matrix
{
public:
	Shape() {}
	Shape(std::initializer_list<Matrix::row> init);
	Shape(std::initializer_list<Vec> init);

	Matrix transform(const Vec& point);
	const Matrix& transform();
	const Matrix& transform(std::initializer_list<Matrix> remote_transforms);

	void add_point(const Vec& point);
	void add_transform(const Matrix& transform);
	void add_transform(std::initializer_list<Matrix::row> init);
	void add_transform(const std::string& name, std::initializer_list<Matrix::row> init);

	Matrix& operator()(const std::string& name);
	const Matrix& operator()(const std::string& name) const;

	const Vec& up() const;
	const Vec& down() const;
	const Vec& left() const;
	const Vec& right() const;
	const Vec& back() const;
	const Vec& front() const;

protected:
	bool _needs_update = true;

	bool has_cache() const;

private:
	std::vector<Matrix> transforms;

	bool validate_transforms() const;
	
	Matrix _cached;
	Matrix _transforms;

	Vec _up{ 4 }, _down{ 4 }, _left{ 4 }, _right{ 4 }, _back{ 4 }, _front{ 4 };
};


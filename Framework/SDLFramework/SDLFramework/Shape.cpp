#include "Shape.h"

Shape::Shape(std::initializer_list<Matrix::row> init)
	: Matrix(init)
{
}

Shape::Shape(std::initializer_list<Vec> init)
	: Matrix(init)
{
}

Matrix Shape::transform(const Vec & point) const
{
	Matrix mat{ point };

	if (!validate_transforms()) {
		throw std::invalid_argument("Malformed transforms");
	}

	bool first_done = false;
	Matrix init = transforms.at(0);

	if (transforms.empty())
		return init;

	for (const Matrix& mat : transforms) {

		if (!first_done) {
			first_done = true;
			continue;
		}

		init = init * mat;
	}

	return init * mat;
}

Matrix Shape::transform() const
{
	return std::move(transform({}));
}

Matrix Shape::transform(std::initializer_list<Matrix> remote_transforms) const
{
	if (!validate_transforms()) {
		throw std::invalid_argument("Malformed transforms");
	}

	bool first_done = false;
	Matrix init = transforms.at(0);

	if (transforms.empty())
		return init;

	for (const Matrix& mat : transforms) {

		if (!first_done) {
			first_done = true;
			continue;
		}

		init = init * mat;
	}

	for (const Matrix& mat : remote_transforms) {
		init = init * mat;
	}

	return std::move(init * (*this));
}

void Shape::add_point(const Vec & point)
{
	add_column(point);
}

void Shape::add_transform(const Matrix & transform)
{
	transforms.push_back(transform);
}

void Shape::add_transform(std::initializer_list<Matrix::row> init)
{
	transforms.push_back(Matrix(init));
}

void Shape::add_transform(const std::string & name, std::initializer_list<Matrix::row> init)
{
	Matrix temp(init);
	temp.name(name);

	transforms.push_back(temp);
}

Matrix & Shape::operator()(const std::string & name)
{
	for (auto& mat : transforms) {
		if (mat.name() == name)
			return mat;
	}

	throw std::out_of_range("No Transform with that name found");
}

const Matrix & Shape::operator()(const std::string & name) const
{
	for (auto& mat : transforms) {
		if (mat.name() == name)
			return mat;
	}

	throw std::out_of_range("No Transform with that name found");
}

bool Shape::validate_transforms() const
{
	if (transforms.empty())
		return false;

	return std::all_of(transforms.begin(), transforms.end(), [this](const Matrix& mat) { return mat.is_compatible(*this); });
}

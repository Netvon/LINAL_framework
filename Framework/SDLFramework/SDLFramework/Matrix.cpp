#include "Matrix.h"

Matrix::Matrix(std::initializer_list<row> init)
{
	size_t vec_size = init.size();
	size_t vec_amount = 0u;

	size_t row_i = 0u;

	for (auto& row : init) {
		if (vec_amount != 0u && vec_amount != row.size()) {
			_valid = false;
			return;
		}

		if (vec_amount == 0) {
			vec_amount = row.size();

			for (size_t i = 0; i < vec_amount; i++)
				_columns.push_back(Vec(vec_size));
		}

		size_t col_i = 0u;
		for (float value : row) {

			auto& vec = _columns.at(col_i);
			vec[row_i] = value;

			col_i++;
		}

		row_i++;
	}

	validate();
}

Matrix::Matrix(std::initializer_list<Vec> init)
	: _columns(init)
{
	validate();
}

Matrix::Matrix(size_t columns, size_t rows, bool identity)
	: _valid{ true }
{
	for (size_t i = 0; i < columns; i++)
	{
		_columns.push_back(Vec(rows));
	}

	if (identity) {
		for (size_t i = 0; i < columns; i++)
		{
			(*this)(i, i) = 1.f;
		}
	}
}

float& Matrix::operator()(size_t y, size_t x) {
	return _columns.at(x)[y];
}

float Matrix::operator()(size_t y, size_t x) const {
	return _columns.at(x)[y];
}

Vec & Matrix::operator[](size_t column_index) {
	return _columns.at(column_index);
}

const Vec & Matrix::operator[](size_t column_index) const {
	return _columns.at(column_index);
}

size_t Matrix::rows() const {
	return _columns.at(0).amount();
}

size_t Matrix::columns() const {
	return _columns.size();
}

Matrix::operator bool() const {
	return _valid;
}

bool Matrix::valid() const {
	return _valid;
}

Matrix Matrix::operator *(const Matrix& b) const {

	auto a = *this;

	if (a.columns() != b.rows()) {
		throw std::out_of_range("amount of columns and rows do not match");
	}

	Matrix mat(b.columns(), a.rows(), false);

	for (size_t y = 0; y < mat.rows(); y++)
	{
		for (size_t x = 0; x < mat.columns(); x++)
		{
			float sum = 0.f;

			for (size_t acol = 0; acol < a.columns(); acol++)
			{
				sum += a(y, acol) * b(acol, x);
			}

			mat(y, x) = sum;
		}
	}

	return mat;
}

Matrix Matrix::operator +(const Matrix b) {
	auto a = *this;

	if (a.rows() != b.rows() || a.columns() != b.columns()) {
		throw std::out_of_range("amount of columns and rows do not match");
	}

	Matrix mat(a.columns(), a.rows(), false);

	for (size_t y = 0; y < mat.rows(); y++)
	{
		for (size_t x = 0; x < mat.columns(); x++)
		{
			mat(y, x) = a(y, x) + b(y, x);
		}
	}

	return mat;
}

Matrix Matrix::operator -(const Matrix b) {
	auto a = *this;

	if (a.rows() != b.rows() || a.columns() != b.columns()) {
		throw std::out_of_range("amount of columns and rows do not match");
	}

	Matrix mat(a.columns(), a.rows(), false);

	for (size_t y = 0; y < mat.rows(); y++)
	{
		for (size_t x = 0; x < mat.columns(); x++)
		{
			mat(y, x) = a(y, x) - b(y, x);
		}
	}

	return mat;
}

Matrix Matrix::operator * (float scalar) const {

	auto a = *this;
	Matrix mat(a.columns(), a.rows(), false);

	for (size_t y = 0; y < mat.rows(); y++)
	{
		for (size_t x = 0; x < mat.columns(); x++)
		{
			mat(y, x) = a(y, x) * scalar;
		}
	}

	return mat;
}

void Matrix::validate()
{
	if (!_columns.empty()) {

		Vec& like = _columns.at(0);
		bool all = std::find_if_not(_columns.begin(), _columns.end(), [like](Vec& val) {
			return val.amount() == like.amount();
		}) == _columns.end();

		if (!all) {
			_columns.clear();
			_valid = false;
		}
	}
}

bool Matrix::operator == (const Matrix& other) const {
	if (other.columns() != columns() || other.rows() != rows())
		return false;

	for (size_t y = 0; y < other.rows(); y++)
	{
		for (size_t x = 0; x < other.columns(); x++)
		{
			if ((*this)(y, x) != other(y, x))
				return false;
		}
	}

	return true;
}

bool Matrix::operator != (const Matrix& other) const {
	return !((*this) == other);
}

Matrix& Matrix::operator=(const Matrix & other)
{
	_columns = other._columns;
	validate();

	return *this;
}


Matrix::iterator Matrix::begin() {
	return _columns.begin();
}

Matrix::iterator Matrix::end() {
	return _columns.end();
}

Matrix::const_iterator Matrix::begin() const {
	return _columns.begin();
}

Matrix::const_iterator Matrix::end() const {
	return _columns.end();
}

std::string Matrix::to_string() const
{
	return std::string();
}

void Matrix::add_column(const Vec & column)
{
	_columns.push_back(column);
	validate();
}

void Matrix::name(const std::string & name)
{
	_name = name;
}

const std::string & Matrix::name() const
{
	return _name;
}

bool Matrix::is_compatible(const Matrix & b) const
{
	auto a = *this;

	if (a.columns() != b.rows()) {
		return false;
	}

	return true;
}

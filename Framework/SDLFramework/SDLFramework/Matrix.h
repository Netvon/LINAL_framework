#pragma once
#include "Vector.h"
#include <stdexcept>
#include <algorithm>
#include <string>

class Matrix {

public:
	typedef std::vector<Vec>::iterator iterator;
	typedef std::vector<Vec>::const_iterator const_iterator;

	typedef std::initializer_list<float> row;

	Matrix() {};

	Matrix(std::initializer_list<row> init);
	Matrix(std::initializer_list<Vec> init);
	Matrix(size_t columns, size_t rows, bool identity = false);

	float& operator()(size_t y, size_t x);
	float operator()(size_t y, size_t x) const;
	Vec & operator[](size_t column_index);

	const Vec & operator[](size_t column_index) const;

	size_t rows() const;
	size_t columns() const;

	operator bool() const;
	bool valid() const;

	Matrix operator * (const Matrix& b) const;
	Matrix operator + (const Matrix b);
	Matrix operator - (const Matrix b);
	Matrix operator * (float scalar) const;

	void validate();

	bool operator == (const Matrix& other) const;
	bool operator != (const Matrix& other) const;

	Matrix& operator = (const Matrix& other);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	std::string to_string() const;

	void add_column(const Vec& column);

	void name(const std::string& name);
	const std::string& name() const;

	bool is_compatible(const Matrix& other) const;
private:
	std::vector<Vec> _columns;
	bool _valid{ true };

	std::string _name{ "<no name>" };
};
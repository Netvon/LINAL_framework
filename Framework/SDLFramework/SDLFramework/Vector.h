#pragma once
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <functional>


class Vec2;
class Vec3;
class Vec4;

class Vec {

public:

	Vec(size_t amount);

	Vec(std::initializer_list<float> init);

	size_t amount() const;

	float& operator[](size_t index) {
		return data.at(index);
	}

	float operator[](size_t index) const {
		return data.at(index);
	}

	Vec operator + (const Vec& other) const {
		return generic_operator([](float a, float b) { return a + b; }, other);
	}

	Vec& operator += (const Vec& other) {
		return generic_operator([](float a, float b) { return a + b; }, other, *this);
	}

	Vec operator - (const Vec& other) const {
		return generic_operator([](float a, float b) { return a - b; }, other);
	}

	Vec& operator -= (const Vec& other) {
		return generic_operator([](float a, float b) { return a - b; }, other, *this);
	}

	Vec operator / (const Vec& other) const {
		return generic_operator([](float a, float b) { return a / b; }, other);
	}

	Vec operator / (float scalar) const {
		return generic_operator([](float a, float b) { return a / b; }, scalar);
	}

	Vec& operator /= (const Vec& other) {
		return generic_operator([](float a, float b) { return a / b; }, other, *this);
	}

	Vec& operator /= (float scalar) {
		return generic_operator([](float a, float b) { return a / b; }, scalar, *this);
	}

	Vec operator * (const Vec& other) const {
		return generic_operator([](float a, float b) { return a * b; }, other);
	}

	Vec operator * (float scalar) const {
		return generic_operator([](float a, float b) { return a * b; }, scalar);
	}

	Vec& operator *= (const Vec& other) {
		return generic_operator([](float a, float b) { return a * b; }, other, *this);
	}

	Vec& operator *= (float scalar) {
		return generic_operator([](float a, float b) { return a * b; }, scalar, *this);
	}

	float length() const;

	Vec normalize() const;

	float distance(const Vec& other) const;

	bool operator == (const Vec& other) const {
		if (_amount != other._amount)
			return false;

		for (size_t i = 0; i < _amount; i++)
		{
			if (data[i] != other.data[i])
				return false;
		}

		return true;
	}

	bool operator != (const Vec& other) const {
		return !((*this) == other);
	}

	operator Vec2();
	operator Vec3();
	operator Vec4();

private:
	std::vector<float> data;
	size_t _amount;

	Vec generic_operator(std::function<float(float, float)> func, float scalar) const;
	Vec& generic_operator(std::function<float(float, float)> func, float scalar, Vec& place_in);
	Vec generic_operator(std::function<float(float, float)> func, const Vec& other) const;
	Vec& generic_operator(std::function<float(float, float)> func, const Vec& other, Vec& place_in) const;
};

class Vec2
	: public Vec
{
public:
	Vec2(float x, float y)
		: Vec{ x, y }
	{

	}

	float x() const;
	float y() const;
	float& x();
	float& y();
};

class Vec3
	: public Vec
{
public:
	Vec3(float x, float y, float z)
		: Vec{ x, y, z }
	{

	}

	float x() const;
	float y() const;
	float z() const;
	float& x();
	float& y();
	float& z();
};

class Vec4
	: public Vec
{
public:
	Vec4(float x, float y, float z, float w)
		: Vec{ x, y, z, w }
	{

	}

	float x() const;
	float y() const;
	float z() const;
	float w() const;
	float& x();
	float& y();
	float& z();
	float& w();
};
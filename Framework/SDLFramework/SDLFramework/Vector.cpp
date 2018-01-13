#include "Vector.h"

Vec::Vec(size_t amount)
	: _amount(amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		data.push_back(0.0f);
	}
}

Vec::Vec(std::initializer_list<float> init)
	: _amount(init.size()), data(init)
{

}

Vec::Vec(const Vec & other)
	: _amount(other._amount), data(other.data)
{
}

size_t Vec::amount() const {
	return _amount;
}

float Vec::length() const {
	float total = 0;

	for (size_t i = 0; i < _amount; i++)
		total += data[i] * data[i];

	return sqrt(total);
}

Vec Vec::normalize() const {
	return (*this) / length();
}

float Vec::distance(const Vec & other) const {
	Vec temp = *this - other;

	return temp.length();
}

float Vec::dot(const Vec & other) const
{
	if (_amount != other._amount) {
		throw std::out_of_range("incompatible Vec");
	}

	float result = 0.f;

	for (size_t i = 0; i < _amount; i++)
	{
		result += (*this)[i] * other[i];
	}

	return result;
}

bool Vec::zero() const
{
	for (auto& f : data) {
		if (f != 0.0f)
			return false;
	}

	return true;
}

Vec Vec::generic_operator(std::function<float(float, float)> func, float scalar) const {
	Vec temp(_amount);

	for (size_t i = 0; i < _amount; i++)
		temp.data[i] = func(data[i], scalar);

	return temp;
}

Vec & Vec::generic_operator(std::function<float(float, float)> func, float scalar, Vec & place_in) {

	for (size_t i = 0; i < _amount; i++)
		data[i] = func(data[i], scalar);

	return place_in;
}

Vec Vec::generic_operator(std::function<float(float, float)> func, const Vec & other) const {
	size_t min_size = std::min(_amount, other._amount);
	size_t max_size = std::max(_amount, other._amount);

	Vec temp(max_size);

	if (min_size == max_size) {
		for (size_t i = 0; i < _amount; i++)
			temp.data[i] = func(data[i], other.data[i]);
	}
	else {
		for (size_t i = 0; i < min_size; i++)
			temp.data[i] = func(data[i], other.data[i]);

		if (_amount == max_size) {

			for (size_t i = min_size; i < max_size; i++)
				temp.data[i] = data[i];

		}
		else {

			for (size_t i = min_size; i < max_size; i++)
				temp.data[i] = other[i];

		}
	}

	return temp;
}

Vec & Vec::generic_operator(std::function<float(float, float)> func, const Vec & other, Vec & place_in) const {
	size_t min_size = std::min(_amount, other._amount);
	size_t max_size = std::max(_amount, other._amount);

	if (min_size == max_size) {
		for (size_t i = 0; i < _amount; i++)
			place_in.data[i] = func(data[i], other.data[i]);
	}
	else {
		for (size_t i = 0; i < min_size; i++)
			place_in.data[i] = func(data[i], other.data[i]);

		if (_amount == max_size) {

			for (size_t i = min_size; i < max_size; i++)
				place_in.data[i] = data[i];

		}
		else {

			for (size_t i = min_size; i < max_size; i++)
				place_in.data[i] = other[i];

		}
	}

	return place_in;
}

float Vec4::x() const {
	return (*this)[0];
}

float Vec4::y() const {
	return (*this)[1];
}

float Vec4::z() const {
	return (*this)[2];
}

float Vec4::w() const {
	return (*this)[3];
}

float & Vec4::x() {
	return (*this)[0];
}

float & Vec4::y() {
	return (*this)[1];
}

float & Vec4::z() {
	return (*this)[2];
}

float & Vec4::w() {
	return (*this)[3];
}

Vec4 Vec4::cross(const Vec4& other) const
{
	return Vec4{
		(y() * other.z()) - (z() * other.y()),
		(z() * other.x()) - (x() * other.z()),
		(x() * other.y()) - (y() * other.x()),
		w()
	};
}

float Vec3::x() const {
	return (*this)[0];
}

float Vec3::y() const {
	return (*this)[1];
}

float Vec3::z() const {
	return (*this)[2];
}

float & Vec3::x() {
	return (*this)[0];
}

float & Vec3::y() {
	return (*this)[1];
}

float & Vec3::z() {
	return (*this)[2];
}

float Vec2::x() const {
	return (*this)[0];
}

float Vec2::y() const {
	return (*this)[1];
}

float & Vec2::x() {
	return (*this)[0];
}

float & Vec2::y() {
	return (*this)[1];
}

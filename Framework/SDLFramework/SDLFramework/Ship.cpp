#include "Ship.h"


Ship::Ship(float x, float y, float z, float width, float height, float depth)
	: Cube3d(x, y, z, width, height, depth)
{

	add_point({ 0.f, -2.f, 0.f, 1.f });
	add_point({ -3.f, 0.f, 0.f, 1.f });
	add_point({ 3.f, 0.f, 0.f, 1.f });
	add_point({ 0.f, -1.f, 0.f, 1.f });

	add_line({ 8llu, 4llu });
	add_line({ 8llu, 5llu });
	add_line({ 8llu, 3llu });
	add_line({ 8llu, 2llu });
	add_line({ 10llu, 9llu });
	add_line({ 11lu, 10llu });
	add_line({ 11llu, 9llu });
}

Ship::~Ship()
{
}

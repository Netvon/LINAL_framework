#include "Cube3d.h"

Cube3d::Cube3d(float x, float y, float z, float width, float height, float depth)
	: Object(x, y, z, width, height, depth)
{
	add_point({ 1.f, 1.f, 1.f, 1.f });
	add_point({ -1.f, 1.f, 1.f, 1.f });
	add_point({ -1.f, -1.f, 1.f, 1.f });
	add_point({ 1.f, -1.f, 1.f, 1.f });

	add_point({ 1.f, 1.f, 1.f, -1.f });
	add_point({ -1.f, 1.f, 1.f, -1.f });
	add_point({ -1.f, -1.f, 1.f, -1.f });
	add_point({ 1.f, -1.f, 1.f, -1.f });


	line_draw_order = {
		{ 0llu, 1llu },
		{ 0llu, 6llu },
		{ 3llu, 0llu },
		{ 3llu, 5llu },
		{ 3llu, 2llu },
		{ 2llu, 4llu },
		{ 4llu, 5llu },
		{ 4llu, 7llu },
		{ 2llu, 1llu },
		{ 7llu, 1llu },
		{ 6llu, 7llu },
		{ 6llu, 5llu },
	};
}

void Cube3d::Update(float deltaTime)
{
}

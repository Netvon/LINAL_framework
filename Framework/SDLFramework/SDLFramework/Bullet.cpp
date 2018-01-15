#include "Bullet.h"



Bullet::Bullet(float x, float y, float z, float width, float height, float depth)
	:Object(x, y, z, width, height, depth)
{
	add_point({ 0.f, 1.f, 0.f, 1.f });
	add_point({ 0.f, -1.f, 0.f, 1.f });

	line_draw_order = {
		{ 0llu, 1llu },
	};
}


Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
}

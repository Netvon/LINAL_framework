#include "DebugDisplay.h"


DebugDisplay::DebugDisplay(std::function<debug_list(void)> create_list, int y_offset, int x_offset)
	: create_list(create_list), _y_offset { y_offset }, _x_offset{ x_offset }
{
}

void DebugDisplay::Update(float deltaTime)
{
	current.clear();
	current = create_list();
}

void DebugDisplay::Draw()
{
	int count = 0;
	Rect last{ _y_offset, _x_offset, 0,0 };
	for (auto& entry : current) {
		int offset = 15;

		if (count == 0) offset = 0;

		Rect size = mApplication->DrawText(entry.first + ": " + entry.second, last.x + last.w + offset, last.y, Color(80,80,80, 255), false);

		if (count > 0) {
			mApplication->SetColor(Color(0, 0, 0, 64));
			mApplication->DrawRect(last.x + last.w + (offset / 2) - 1, last.y + 7, 3, 3, true);
		}

		last = size;
		count++;
	}
}

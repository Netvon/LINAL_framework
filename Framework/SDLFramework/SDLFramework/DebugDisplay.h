#pragma once
#include "IGameObject.h"
#include <functional>
#include <vector>
#include <string>

class DebugDisplay : public IGameObject
{
public:
	typedef std::vector<std::pair<std::string, std::string>> debug_list;
	DebugDisplay(std::function<debug_list(void)> create_list, int y_offset = 0, int x_offset = 0);
	~DebugDisplay() {};

	// Inherited via IGameObject
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	std::function<debug_list(void)> create_list;

	debug_list current;

	int _x_offset{ 1 };
	int _y_offset{ 5 };
};


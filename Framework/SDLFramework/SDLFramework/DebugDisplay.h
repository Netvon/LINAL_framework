#pragma once
#include "IGameObject.h"
#include <functional>
#include <vector>
#include <string>

class DebugDisplay : public IGameObject
{
public:
	typedef std::vector<std::pair<std::string, std::string>> debug_list;
	DebugDisplay(std::function<debug_list(void)> create_list);
	~DebugDisplay() {};

	// Inherited via IGameObject
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	std::function<debug_list(void)> create_list;

	debug_list current;
};


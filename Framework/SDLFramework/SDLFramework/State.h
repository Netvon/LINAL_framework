#include "FWApplication.h"
#pragma once

template<typename TOwner>
class State
{
public:
	State() {};
	State(TOwner* owner): owner(owner) { };
	virtual ~State() {};

	virtual void move(float delta_time) = 0;
	virtual void checkState() = 0;
	virtual void enteredState() = 0;

	virtual const char* name() {
		return "<no name>";
	}

	virtual const Color color() {
		return Color(0, 0, 0, 0);
	}

protected:
	TOwner* owner = nullptr;
};


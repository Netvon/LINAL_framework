#pragma once
#include "IGameObject.h"
#include <memory>
#include "State.h"
#include <typeindex>
#include <map>

template<typename TOwner>
class ObjectWithState :
	public IGameObject
{
public:
	typedef std::shared_ptr<State<TOwner>> state_ptr;
	typedef std::vector<state_ptr> state_list;
	typedef std::size_t state_index;
	typedef std::map<std::type_index, std::size_t> state_type_map;

	ObjectWithState() {};
	~ObjectWithState() {};

	std::shared_ptr<State<TOwner>> state() const 
	{
		if (states.empty())
			return nullptr;
		
		return states.at(current_state);
	}

	template<typename TState>
	void setState();

	bool has_state() const;

protected:
	template<typename TState, typename...TArgs>
	void addState(TArgs&&... arguments);

private:
	state_index current_state = 0llu;
	state_list states;
	state_type_map map;

	// Inherited via IGameObject
	virtual void Update(float deltaTime) override 
	{
		move(deltaTime);
		auto s = state();

		if (s) {
			s->checkState();
		}

		s = state();

		if (s) {
			//FWApplication::GetInstance()->DrawText(s->name(), getCurrentVertex().getX(), getCurrentVertex().getY() - 25, Color(255, 255, 255, 255));
			s->move(deltaTime);
		}
	};

	virtual void move(float deltaTime) = 0;
};

template<typename TOwner>
template<typename TState, typename ...TArgs>
void ObjectWithState<TOwner>::addState(TArgs && ...arguments)
{	
	states.emplace_back(std::make_shared<TState>(std::forward<TArgs>(arguments)...));
	map.emplace(std::type_index(typeid(TState)), states.size() - 1llu);
}

template<typename TOwner>
template<typename TState>
void ObjectWithState<TOwner>::setState()
{
	auto type_index = std::type_index(typeid(TState));

	auto it = map.find(type_index);

	if (it != map.end()) {
		current_state = it->second;

		state()->enteredState();
	}
}

template<typename TOwner>
bool ObjectWithState<TOwner>::has_state() const
{
	return states.size() > 0;
}

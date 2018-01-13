#pragma once
#include "IGameObject.h"
#include "Vector.h"

#include <memory>

class ForceEntity :
	public IGameObject
{
public:
	virtual ~ForceEntity() {};

	const Vec3& location() const;
	const Vec3& velocity() const;

	float movement_speed() const;
	void movement_speed(float new_value);

	// Inherited via IGameObject
	virtual void Update(float deltaTime) override;

protected:
	Vec3 _velocity{ 0.f, 0.f, 0.f };
	Vec3 _location{ 0.f, 0.f, 0.f };

	float _movement_speed = 10.f;

private:
	void update_location(float deltaTime);

	virtual void additional_update(float deltaTime) { };
};

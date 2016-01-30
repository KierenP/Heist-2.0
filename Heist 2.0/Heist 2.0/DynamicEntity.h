#pragma once
#include "StaticEntity.h"

//A type of Entity that can move around. Has Velocity and Accelleration

class DynamicEntity : public StaticEntity
{
public:
	DynamicEntity(sf::Vector2f position, float direction, sf::Texture texture, sf::Vector2f velocity = sf::Vector2f(0, 0), sf::Vector2f acceleration = sf::Vector2f(0, 0));
	virtual ~DynamicEntity();

	sf::Vector2f GetVelocity() { return mVelocity; }
	sf::Vector2f GetAcceleration() { return mAcceleration; }

	void SetVelocity(sf::Vector2f val) { mVelocity = val; }
	void SetAcceleration(sf::Vector2f val) { mAcceleration = val; }

	void UpdateEntity(float deltaTime);

protected:
	sf::Vector2f mVelocity;
	sf::Vector2f mAcceleration;
};


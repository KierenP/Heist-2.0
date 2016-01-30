#include "DynamicEntity.h"

DynamicEntity::DynamicEntity(sf::Vector2f position, float direction, sf::Texture texture, sf::Vector2f velocity, sf::Vector2f acceleration)	: StaticEntity(position, direction, texture)
{
	mVelocity = velocity;
	mAcceleration = acceleration;
}

DynamicEntity::~DynamicEntity()
{
}

void DynamicEntity::UpdateEntity(float deltaTime)
{
	mVelocity += mAcceleration * deltaTime;
	mPosition += mVelocity * deltaTime;
}


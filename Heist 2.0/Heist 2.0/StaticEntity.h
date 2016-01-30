#ifndef ENTITY_H
#define ENTITY_H

#include "FunctionLib.h"
#include "SFML\Graphics.hpp"

/*
A stationary object with a position, direction, and visual sprite
*/

class StaticEntity
{
public:
	//StaticEntity() {}
	StaticEntity(sf::Vector2f position, float direction, sf::Texture texture) : mPosition(position), mDirection(direction), mTexture(texture) {}
    virtual ~StaticEntity() {}

	sf::Vector2f GetPosition()			{ return mPosition; }
	float GetDirection()				{ return mDirection; }
	sf::Texture GetTexture()			{ return mTexture; }
	sf::Sprite GetSprite()				{ return mSprite; }

	void SetPosition(sf::Vector2f val)	{ mPosition = val; UpdateSprite(); }
	void SetDirection(float val)		{ mDirection = val;  UpdateSprite(); }
	void SetSprite(sf::Sprite val)		{ mSprite = val; }
	void SetTexture(sf::Texture val)	{ mTexture = val; }

	void PointTowards(sf::Vector2f point);

	void RenderSprite(sf::RenderWindow& renderTarget);

protected:
	float mDirection;
	sf::Vector2f mPosition;
	sf::Texture mTexture;
	sf::Sprite mSprite;

private:
	void UpdateSprite();
};

#endif //ENTITY_H

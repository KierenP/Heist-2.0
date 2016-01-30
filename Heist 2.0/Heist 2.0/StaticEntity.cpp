#include "StaticEntity.h"

void StaticEntity::PointTowards(sf::Vector2f point)
{
	float x = mPosition.x - point.x;
	float y = mPosition.y - point.y;

	mDirection = FunctionLib::ToDegrees(atan2f(y, x));
}

void StaticEntity::UpdateSprite()
{
	mSprite.setPosition(mPosition);
	mSprite.setTexture(mTexture);
	mSprite.setRotation(mDirection);
}

void StaticEntity::RenderSprite(sf::RenderWindow & renderTarget)
{
	renderTarget.draw(mSprite);
}

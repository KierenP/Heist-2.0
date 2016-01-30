#include "Projectile.h"

Projectile::Projectile(sf::Vector2f position, float direction, float velocity, float damage, sf::Texture spriteTexture) : DynamicEntity(position, direction, spriteTexture, CalculateVelocities(velocity, direction))
{

}

Projectile::~Projectile()
{

}

sf::Vector2f Projectile::CalculateVelocities(float direction, float velocity)
{
    float VelX = FunctionLib::ToDegrees(cos(FunctionLib::ToRadians(direction))) * velocity;
    float VelY = FunctionLib::ToDegrees(sin(FunctionLib::ToRadians(direction))) * velocity;

	return sf::Vector2f(VelX, VelY);
}

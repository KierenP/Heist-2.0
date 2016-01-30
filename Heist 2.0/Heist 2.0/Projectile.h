#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include "DynamicEntity.h"
#include "FunctionLib.h"
#include <cmath>
#include <SFML/Graphics.hpp>

class Projectile : public DynamicEntity
{
public:
	Projectile(sf::Vector2f position, float direction, float velocity, float damage, sf::Texture spriteTexture);
    ~Projectile();

    float GetDamage() { return mDamage; }
    void SetDamage(float val) { mDamage = val; }

private:
	sf::Vector2f Projectile::CalculateVelocities(float direction, float velocity);       //Based on a direction and a velocity calculate the velocity x and y

    float mDamage;
};

#endif // PROJECTILE_H_INCLUDED

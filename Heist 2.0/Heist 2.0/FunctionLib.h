#ifndef FUNCTIONLIB_H
#define FUNCTIONLIB_H

#include "StaticEntity.h"
#include "SFML/Graphics.hpp"

const float Pi = 3.14f;

namespace FunctionLib
{
    float DistanceBetween(float x1, float y1, float x2, float y2);
    float ToDegrees(float radians);
    float ToRadians(float degrees);
    float DirectionToPoint(float x1, float y1, float x2, float y2);				//returns in radians the angle from a(x, y) to b(x, y) 

    std::vector<sf::Vector2f> GenerateBoxFromSprite(sf::Sprite& sprite);
    std::vector<sf::Vector2f> GenerateBoxFromDimentions(float posX, float posY, float width, float height);
}

#endif // FUNCTIONLIB_H

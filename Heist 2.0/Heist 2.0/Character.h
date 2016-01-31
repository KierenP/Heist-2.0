#pragma once

#include "StaticEntity.h"
#include "PlayerStats.h"

struct KeyState{		//possibly irrelivent, if key states are needed, sf::Keyboard::IsKeyPressed:: (or somthing of the like) can be used on demand
    bool UpPressed;
    bool DownPressed;
    bool LeftPressed;
    bool RightPressed;
    bool LMBPressed;
};

class Character : public PlayerData, public StaticEntity
{
public:
	Character(StaticEntity pEntity, PlayerData pStats) : PlayerData(pStats), StaticEntity(pEntity) {}
	Character(sf::Vector2f position, float direction, sf::Texture texture, PlayerData pStats) : PlayerData(pStats), StaticEntity(position, direction, texture) {}
    ~Character();

    sf::Clock GetWeaponClock() { return mWeaponCoolDownClock; }	
    void SetWeaponClock(sf::Clock val) { mWeaponCoolDownClock = val; }				//same again

    void Render(sf::RenderWindow& renderTarget);									//possibly redundant due to StaticEntity::RenderSprite()
    void Update(float deltaTime, KeyState moveDirection, bool willCollide);			//Update the players mSprite and position, as well as the mProjectiles

private:
    void UpdateSprite();															//Update the mSprite
    void Move(KeyState moveDirection, float timeStep);								//Move the player in the passed directions
														
    sf::Clock mWeaponCoolDownClock;
};


#pragma once

#include "StaticEntity.h"
#include "PlayerStats.h"
#include "TileEngine.h"

struct KeyState{		//possibly irrelivent, if key states are needed, sf::Keyboard::IsKeyPressed:: (or somthing of the like) can be used on demand
    bool UpPressed;
    bool DownPressed;
    bool LeftPressed;
    bool RightPressed;
    bool LMBPressed;
};

class BaseCharacter : public PlayerData, public StaticEntity
{
public:
	BaseCharacter(StaticEntity pEntity, PlayerData pStats) : PlayerData(pStats), StaticEntity(pEntity) {}
	BaseCharacter(sf::Vector2f position, float direction, sf::Texture texture, PlayerData pStats) : PlayerData(pStats), StaticEntity(position, direction, texture) {}
    virtual ~BaseCharacter();

    sf::Clock GetWeaponClock() { return mWeaponCoolDownClock; }	
    void SetWeaponClock(sf::Clock val) { mWeaponCoolDownClock = val; }				//same again

    void Render(sf::RenderWindow& renderTarget);									//possibly redundant due to StaticEntity::RenderSprite()
    void Update(float deltaTime, KeyState moveDirection, bool willCollide);			//Update the players mSprite and position, as well as the mProjectiles
	virtual void CalculateAim(std::vector<BaseCharacter>& targets, TileEngine& gameworld) = 0;
	virtual void CalculateMovement(std::vector<BaseCharacter>& targets, TileEngine& gameworld) = 0;

private:
    void UpdateSprite();															//Update the mSprite
    void Move(KeyState moveDirection, float timeStep);								//Move the player in the passed directions
														
    sf::Clock mWeaponCoolDownClock;
};


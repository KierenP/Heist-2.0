#ifndef CHARACTER_H
#define CHARACTER_H

#include "StaticEntity.h"
#include "PlayerStats.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>

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

    std::vector<Projectile> GetProjectiles()	{ return mProjectiles; }			//Note function below for just getting one of the projectiles, thats faster is thats what you want
    sf::Clock GetWeaponClock()					{ return mWeaponCoolDownClock; }	
    
    void SetSprite(sf::Sprite val) { mSprite = val; }								//Not sure why you'd want to do this, but here it is
    void SetProjectiles(std::vector<Projectile> val) { mProjectiles = val; }		//Yea got no idea who would use that, but it could be usefull
    void SetWeaponClock(sf::Clock val) { mWeaponCoolDownClock = val; }				//same again

    void Render(sf::RenderWindow& renderTarget);									//Draw the player sprite and its mProjectiles
    void GenerateProjectile();														//Create a new Projectile object push_back it to mProjectiles
    void RemoveProjectile(unsigned int index);										//Remove Projectile at given position in mProjectiles
    void Update(float deltaTime, KeyState moveDirection, bool willCollide);			//Update the players mSprite and position, as well as the mProjectiles
	Projectile GetProjectile(unsigned int index);									//Return a copy of the Projectile stored in mProjectiles at given index

	std::vector<Projectile> mProjectiles;

private:
    void RenderProjectiles(sf::RenderWindow& pTarget);								//Draw each Projectiles in mProjectiles's mSprite
    void UpdateProjectiles(float timeStep);											//Update each Projectiles in mProjectiles's position based off given time since last update
    void UpdateSprite();															//Update the mSprite
    void Move(KeyState moveDirection, float timeStep);								//Move the player in the passed directions
														
    sf::Clock mWeaponCoolDownClock;
};

#endif // CHARACTER_H

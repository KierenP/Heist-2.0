#pragma once
#include "WeaponStats.h"
#include <SFML\Graphics.hpp>

//I Split the very large Character class into two by putting all the data and management into this class, which is inherited by Character

class PlayerData			
{
public:
	PlayerData() {}
	PlayerData(float speed, float health, unsigned int teamNumber, WeaponStats weapon, bool isPlayerControlled);
	virtual ~PlayerData() {}

	//Getters
	float GetSpeed() { return mSpeed; }
	float GetHealth() { return mHealth; }
	unsigned int GetTeam() { return mTeamNumber; }
	WeaponStats GetWeapon() { return mWeapon; }
	bool GetIsPlayerControlled() { return mIsPlayerControlled; }

	//Setters
	void SetSpeed(float val) { mSpeed = val; }
	void SetHealth(float val);
	void SetTeam(unsigned int val) { mTeamNumber = val; }
	void SetWeapon(WeaponStats val) { mWeapon = val; }
	void SetIsPlayerControlled(bool val) { mIsPlayerControlled = val; }

protected:
	float mSpeed;
	float mHealth;
	unsigned int mTeamNumber;
	WeaponStats mWeapon;
	bool mIsPlayerControlled;
};
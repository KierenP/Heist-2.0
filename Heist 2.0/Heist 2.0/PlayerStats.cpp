#include "PlayerStats.h"

PlayerData::PlayerData(float speed, float health, unsigned int teamNumber, WeaponStats weapon, bool isPlayerControlled)
{
	mSpeed = speed;
	mHealth = health;
	mTeamNumber = teamNumber;
	mWeapon = weapon;
	mIsPlayerControlled = isPlayerControlled;
}

void PlayerData::SetHealth(float val)
{
	mHealth = val;

	if (mHealth < 0)
		mHealth = 100;
}

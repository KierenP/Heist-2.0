#include "Character.h"

Character::~Character()
{
	
}

void Character::Render(sf::RenderWindow& pTarget)
{
	mSprite.setTexture(mTexture);	//This *should* not be nessisary, but is.
    pTarget.draw(mSprite);
    RenderProjectiles(pTarget);		
}

void Character::RenderProjectiles(sf::RenderWindow& pTarget)
{
	for (unsigned int iProjectile = 0; iProjectile < mProjectiles.size(); iProjectile++)
    {
		mProjectiles[iProjectile].RenderSprite(pTarget);
    }
}

void Character::RemoveProjectile(unsigned int index)
{
    if (index >= mProjectiles.size())					//Saftey check that the index in in bounds of array. No need to check for < 0, because index is unsigned (always positive)
        return;
    mProjectiles.erase(mProjectiles.begin() + index);
}

void Character::UpdateSprite()
{
	mSprite.setTexture(mTexture);
    mSprite.setPosition(mPosition.x, mPosition.x);
    mSprite.setRotation(mDirection + 90);			//Todo: take away the +90, and re orientent sprites in paint
}

void Character::UpdateProjectiles(float timeStep)
{
	for (unsigned int iProjectile = 0; iProjectile < mProjectiles.size(); iProjectile++)
    {
		mProjectiles[iProjectile].UpdateEntity(timeStep);
    }
}

void Character::Update(float timeStep, KeyState val, bool willCollide)
{
	if (!willCollide)   //LevelEntityManager will pass a true of false wether it is allowed to move
		Move(val, timeStep);

    UpdateSprite();

    if (val.LMBPressed && mWeaponCoolDownClock.getElapsedTime().asMilliseconds() > mWeapon.mFireRate)
    {
        GenerateProjectile();
		mWeaponCoolDownClock.restart();
    }

	UpdateProjectiles(timeStep);
}

void Character::Move(KeyState var, float TimeStep)
{
    if (var.UpPressed)
		mPosition.y -= mSpeed * TimeStep;
    if (var.DownPressed)
		mPosition.y += mSpeed * TimeStep;
    if (var.LeftPressed)
		mPosition.x -= mSpeed * TimeStep;
    if (var.RightPressed)
		mPosition.x += mSpeed * TimeStep;
}

void Character::GenerateProjectile()
{
    float RandDirection = mDirection + (-1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2)))) * mWeapon.mBulletSpred;         //Random number between (-1 and +1 * Spread)

    mProjectiles.push_back(Projectile(mPosition, RandDirection, mWeapon.mBulletSpeed, mWeapon.mDamage, mWeapon.mBulletTexture));
}

Projectile Character::GetProjectile(unsigned int index)
{
	return mProjectiles[index];
}


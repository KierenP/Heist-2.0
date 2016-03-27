#include "BaseCharacter.h"

BaseCharacter::~BaseCharacter()
{
	
}

void BaseCharacter::Render(sf::RenderWindow& pTarget)
{
    pTarget.draw(mSprite);
}

void BaseCharacter::UpdateSprite()
{
	mSprite.setTexture(mTexture);
    mSprite.setPosition(mPosition.x, mPosition.y);
    mSprite.setRotation(mDirection - 90);			//Todo: take away the -90, and re orientent sprites in paint
	mSprite.setOrigin(mTexture.getSize().x / 2, mTexture.getSize().y / 2);
}

void BaseCharacter::Update(float timeStep, KeyState val, bool willCollide)
{
	if (!willCollide)   //LevelEntityManager will pass a true of false wether it is allowed to move
		Move(val, timeStep);

    UpdateSprite();

    if (val.LMBPressed)// && mWeaponCoolDownClock.getElapsedTime().asMilliseconds() > mWeapon.mFireRate)
    {
		mWeaponCoolDownClock.restart();
    }
}

void BaseCharacter::Move(KeyState var, float TimeStep)
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

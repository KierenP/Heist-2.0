    #ifndef WEAPONSTATS_H_INCLUDED
    #define WEAPONSTATS_H_INCLUDED

    #include <SFML/Graphics.hpp>

    struct WeaponStats
    {
        float mDamage;
        float mBulletSpeed;			//pixles per second
        float mFireRate;			//miliseconds cooldown between shots
        float mBulletSpred;			//degrees +/- the shot can land
        sf::Texture mBulletTexture;
    };

    enum WeaponTypes
    {
        RifleWeapon,
        SMGWeapon,
        ShotGunWeapon,
    };

    WeaponStats GetWeaponStat(WeaponTypes weaponID);


    #endif // WEAPONSTATS_H_INCLUDED

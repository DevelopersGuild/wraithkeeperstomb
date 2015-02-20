#include "Spear.h"
#include "Constants.h"
#include "Weapons.h"

Spear::Spear()
{
	WeaponTexture.loadFromFile("../assets/sprites/spear.png");
	WeaponSprite.setTexture(WeaponTexture);
	WeaponSprite.setOrigin(32, 128); // change this

	range = SPEAR_RANGE;
	cooldown = SPEAR_COOLDOWN;
	crit_chance = SPEAR_CRIT_CHANCE;
	crit_multiplier = SPEAR_CRIT_MULTIPLIER;
	damage_fluctuation = SPEAR_DMG_FLUCTUATION_RATE * SPEAR_DAMAGE;
	damage = dmgRandomizer(damage_fluctuation) * critical(crit_multiplier);

	srand(time(0));
}

Spear::~Spear()
{

}
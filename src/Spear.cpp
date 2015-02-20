#include "Spear.h"
#include "Constants.h"

Spear::Spear(Hero *hero)
{
	WeaponTexture.loadFromFile("../assets/sprites/spear1.png");
	WeaponSprite.setTexture(WeaponTexture);
	WeaponSprite.setOrigin(32, 128); // change this
	WeaponSprite.setPosition(hero->getX(), hero->getY());

	cooldown.restart().asSeconds();
	range = SPEAR_RANGE;
	crit_chance = SPEAR_CRIT_CHANCE;
	crit_multiplier = SPEAR_CRIT_MULTIPLIER;
	damage_fluctuation = SPEAR_DMG_FLUCTUATION_RATE * SPEAR_DAMAGE;
	damage = dmgRandomizer(damage_fluctuation) * critical(crit_multiplier);

	srand(time(0));
}

Spear::~Spear()
{

}
#include "Spear.h"
#include "Constants.h"
#include <iostream>

Spear::Spear(Hero *hero)
{
	Texture.loadFromFile("../assets/sprites/spear1.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(30, 137); // change this
	Sprite.setPosition(hero->getX(), hero->getY());

	cooldown.restart().asSeconds();
	damage = SPEAR_DAMAGE;
	range = SPEAR_RANGE;
	crit_chance = SPEAR_CRIT_CHANCE;
	crit_multiplier = SPEAR_CRIT_MULTIPLIER;
	damage_fluctuation = SPEAR_DMG_FLUCTUATION_RATE * SPEAR_DAMAGE;
	damage = dmgRandomizer(damage_fluctuation) * critical(crit_multiplier);

	srand((unsigned int)time(NULL));
}

const sf::FloatRect Spear::getCollisionRect(Hero *hero)
{
	sf::FloatRect collisionRect(hero->getX(), hero->getY(), range, 32.f);
	return collisionRect;
}

bool Spear::attack()
{
	if (cooldown.getElapsedTime().asSeconds() > SPEAR_COOLDOWN)
	{
		//Show animation here
		cooldown.restart().asSeconds();
		return true;
	}
	else
		return false;
}

void Spear::update()
{
	
}

Spear::~Spear()
{

}
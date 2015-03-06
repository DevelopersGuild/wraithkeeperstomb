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

void Spear::attack(Hero* hero, Entity* &enemy)
{
	if (cooldown.getElapsedTime().asSeconds() > SPEAR_COOLDOWN)
	{
		sf::FloatRect collisionRect(hero->getX(), hero->getY() - 137, range, 32.f); //137 = y-origin of spear
		//Show animation here
		if (collisionRect.intersects(enemy->getCollisionRect()))
		{
			enemy->onHit(damage);
		}
		cooldown.restart().asSeconds();
	}
}

void Spear::update(Hero* hero, Entity* &enemy)
{
	// attack
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		attack(hero, enemy);
	}
}

Spear::~Spear()
{

}
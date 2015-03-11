#include "Spear.h"
#include "Constants.h"
#include <iostream>

Spear::Spear(Hero *hero)
{
	Texture.loadFromFile("../assets/sprites/spear1.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 64); // change this
	Sprite.setPosition(hero->getX(), hero->getY());

	cooldown.restart().asSeconds();
	damage = SPEAR_DAMAGE;
	range = SPEAR_RANGE;
	crit_chance = SPEAR_CRIT_CHANCE;
	crit_multiplier = SPEAR_CRIT_MULTIPLIER;
	damage_fluctuation = SPEAR_DMG_FLUCTUATION_RATE * SPEAR_DAMAGE;
	damage = dmgRandomizer(damage_fluctuation) * critical(crit_multiplier);

	sf::Vector2i anim(sf::Vector2i(0, 0));

	srand((unsigned int)time(NULL));
}

void Spear::stabAnim()
{
	if (atkTime > 34)
		anim.y = 1;
	else if (atkTime > 13)
		anim.y = 2;
	else
		anim.y = 1;
	atkTime--;
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
		atkTime = 50;
		cooldown.restart().asSeconds();
		return true;
	}
	else
		return false;
}

void Spear::update(bool faceRight)
{
	if (atkTime > -7)
		stabAnim();
	else
		anim.y = 0;
	if (faceRight)
		Sprite.setScale(1, 1);
	else
		Sprite.setScale(-1, 1);
	Sprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 64, 64, 64));
}

Spear::~Spear()
{

}
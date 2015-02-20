#ifndef SPEAR_H
#define SPEAR_H

#include "Weapons.h"
#include "Game.h"

class Spear : public Weapons
{
private:
	sf::Clock cooldown;
public:
	Spear(Hero *);
	virtual ~Spear();
	const sf::Clock getCooldown()
	{ return cooldown; }
	const sf::FloatRect getCollisionRect()
	{ return Sprite.getGlobalBounds(); }
	const sf::Sprite getSprite()
	{ return WeaponSprite; }
};


#endif
#ifndef SPEAR_H
#define SPEAR_H

#include "Weapons.h"
#include "Hero.h"
#include "Game.h"
#include "Enemies.h"

class Spear : public Weapons
{
private:
	sf::Clock cooldown;
public:
	Spear(Hero *);
	virtual ~Spear();
	const sf::Clock getCooldown()
	{ return cooldown; }
	const sf::Sprite getSprite()
	{ return Sprite; }
	const sf::FloatRect getCollisionRect(Hero *);
	void update(Hero *, Entity *&);
	void attack(Hero *, Entity *&);

};

#endif

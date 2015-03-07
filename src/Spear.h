#ifndef SPEAR_H
#define SPEAR_H

#include "Weapons.h"
#include "Hero.h"
#include "Game.h"
#include "Enemies.h"

class Spear : public Weapons
{
public:
	Spear(Hero *);
	virtual ~Spear();
	const sf::Clock getCooldown()
	{ return cooldown; }
	const sf::Sprite getSprite()
	{ return Sprite; }
	const sf::FloatRect getCollisionRect(Hero *);
	void update();
	bool attack();

};

class Spear2 : public Spear
{
public:
	Spear2(Hero *hero) :Spear(hero)
	{
		Texture.loadFromFile("../assets/sprites/spear2.png");
		Sprite.setTexture(Texture);
		Sprite.setOrigin(32, 128);
		Sprite.setPosition(280, 1360);
	}
};

#endif

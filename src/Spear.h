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

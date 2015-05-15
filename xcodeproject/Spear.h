#ifndef SPEAR_H
#define SPEAR_H

#include "Weapons.h"
#include "Hero.h"
#include "Game.h"
#include "Enemy.h"

class Spear : public Weapons
{
private:
	void stabAnim();
	int atkTime;
public:
	Spear(Hero *);
	virtual ~Spear();
	const sf::Sprite getSprite()
	{ return Sprite; }
	const sf::FloatRect getCollisionRect(Hero *);
	void update(bool);
	bool attack();

};

class Spear2 : public Spear
{
public:
	Spear2(Hero *hero) :Spear(hero)
	{
		sf::Vector2i anim(sf::Vector2i(0, 0));
		Texture.loadFromFile("../assets/sprites/spear2.png");
		Sprite.setTexture(Texture);
		Sprite.setOrigin(32, 64);
		Sprite.setPosition(280, 1360);
		Sprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 64, 64, 64));

		damage = SPEAR2_DAMAGE;
		crit_chance = SPEAR2_CRIT_CHANCE;
	}
};

#endif

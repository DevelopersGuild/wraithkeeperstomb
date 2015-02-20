#ifndef ENEMIES_H
#define ENEMIES_H

#include "Hero.h"
#include "Entity.h"

class Enemies: public Entity
{
protected:
	int damage;
	bool isAlive;
	int HP;
	float armor;
	float speed;
	float speedMultiplier;
	void onHit(float dmg);
public:
	Enemies();
	virtual ~Enemies() { }
	bool heroDetection(Hero* hero);
	void chaseHero();
	void left();
	void right();
	virtual void onHeroDetected(Hero* hero);
	// void onHit(); // only if the enemy has armor

	// Accessor(s)
	const float getDamage()
	{ return damage; }
	const bool getAlive()
	{ return isAlive; }
	const int getHP()
	{ return HP; }
	void onHit(int dmg);
};

#endif

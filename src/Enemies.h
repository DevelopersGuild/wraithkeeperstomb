#ifndef ENEMIES_H
#define ENEMIES_H

#include "Hero.h"
#include "Entity.h"

class Enemies: public Entity
{
protected:
	float damage;
	bool isAlive;
	float HP;
	float armor;
	float speed;
	float speedMultiplier;
public:
	Enemies();
	virtual ~Enemies() { }
	bool heroDetection(Hero* hero);
	void chaseHero();
	void left();
	void right();
	virtual void onHeroDetected(Hero* hero);
	void onHit(float dmg);

	// Accessor(s)
	const float getDamage()
	{ return damage; }
	const bool getAlive()
	{ return isAlive; }
	const float getHP()
	{ return HP; }
	void onHit(int dmg);
};

#endif

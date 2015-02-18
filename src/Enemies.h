#ifndef ENEMIES_H
#define ENEMIES_H
#include "Hero.h"
#include "Entity.h"

class Enemies: public Entity
{
protected:
	int damage;
public:
	Enemies();
	virtual ~Enemies() { }
	bool heroDetection(Hero* hero);
	void chaseHero();
	virtual void onHeroDetected(Hero* hero);
	// void onHit(); // only if the enemy has armor

	// Accessor(s)
	int getDamage() { return damage; }

	void onHit(int dmg);
};

#endif

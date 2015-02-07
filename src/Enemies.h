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
	void update(Hero* hero); // may need to be made virtual
	bool heroDetection(Hero* hero);
	virtual void onHeroDetected(Hero* hero);
	// void onHit(); // only if the enemy has armor

	// Accessor(s)
	int getDamage() { return damage; }
};

#endif

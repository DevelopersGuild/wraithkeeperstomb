#ifndef ENEMIES_H
#define ENEMIES_H

#include "Hero.h"
#include "Entity.h"

class Enemies: public Entity
{
protected:
	float damage;
	float HP;
	float armor;
	float speed;
	float speedMultiplier;
	bool isChase;
	sf::Clock Freeze;
	sf::RectangleShape hpbar_;

public:
	Enemies();
	virtual ~Enemies() { }
	bool heroDetection(Hero* hero);
	void chaseHero();
	void left();
	void right();
	virtual void jump(){
		
	}
	virtual void onHeroDetected(Hero* hero);
	void onHit(float dmg);
	void freeze();
	void knockBack(Entity *hitter);

	// Accessor(s)
	const float getDamage()
	{ return damage; }

	const float getHP()
	{ return HP; }

	void onHit(int dmg);
};

#endif

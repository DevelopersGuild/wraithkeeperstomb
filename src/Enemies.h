#ifndef ENEMIES_H
#define ENEMIES_H

#include "Hero.h"
#include "Entity.h"

class Enemies: public Entity
{
protected:
	bool faceRight;//NEED: enemy animation
	float damage;
	float HP;
	float armor;
	float speed;
	float speedMultiplier;
	bool isShooter; //used later
	bool isChase;
	bool heroDetected;
	sf::Clock Freeze;
	sf::RectangleShape hpbar_;
	float patrol_origin; //x-value only for now
	bool patrol_right;
	float patrol_pause;

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
	void knockBack(float, float);
	void areaPatrol(float);

	// Accessor(s)
	const float getDamage()
	{ return damage; }

	const float getHP()
	{ return HP; }

	const bool get_isShooter()
	{ return isShooter; }

	const bool getFaceRight()
	{ return faceRight; }

	void onHit(int dmg);
};

#endif

#ifndef ENEMIES_H
#define ENEMIES_H

#include "Hero.h"
#include "Entity.h"

class Enemy: public Entity
{
protected:
	bool faceRight;//NEED: enemy animation
	float damage;
	float HP;
	float armor;
	float speed;
	float speedMultiplier;
	bool isShooter; //used later
	bool isFrozen;
	bool heroDetected;
	bool wasPaused;
	sf::Clock Freeze;
	sf::RectangleShape hpbar_;
	float patrol_origin; //x-value only for now
	bool patrol_right;
	float patrol_pause;
	//char backing;
	float knockBackDuration;
	float left_bound;
	float right_bound;
	int xFrame;
	int yFrame;
	int frameTimer;

public:
	Enemy();
	virtual ~Enemy() { }
	virtual bool heroDetection(Hero* hero);
	void chaseHero();
	void left();
	void right();
	virtual void jump(){
		
	}
	virtual void onHeroDetected(Hero* hero);
	float onHit(float dmg);
	void freeze();
	void knockBack(float);
	void areaPatrol(float);
	void setPatrolBoundary(float, float);

	// Accessor(s)
	const float getDamage()
	{ return damage; }

	const float getHP()
	{ return HP; }

	const bool get_isShooter()
	{ return isShooter; }

	const bool getFaceRight()
	{ return faceRight; }

	const bool getHeroDetected()
	{ return heroDetected; }

	virtual const sf::FloatRect getDamagingRect()
	{// shrink the bounding box
		float left = Sprite.getGlobalBounds().left + 30;
		float top = Sprite.getGlobalBounds().top + 20;
		float width = Sprite.getGlobalBounds().width - 60;
		float height = Sprite.getGlobalBounds().height - 40;
		sf::FloatRect collisionRect(left, top, width, height);
		return collisionRect;
	}

	const void set_patrol_origin(float x_pos)
	{
		patrol_origin = x_pos;
	}

	void onHit(int dmg);
	//void backDirection(float, float);
};

#endif

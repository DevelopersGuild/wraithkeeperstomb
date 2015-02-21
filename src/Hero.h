#ifndef HERO_H
#define HERO_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

class Hero : public Entity
{
private:
	sf::Vector2f velocity;
	sf::Vector2i anim;		//Tracker for hero sprite frames

	float speed;
	float speedMultiplier;
	int armor;
	int collisionNum;
	int HP;
	int xFrame;					//Current frame in the x grid
	int yFrame;					//Current frame in the y grid
	int frameTimer;				//Counter for sprite frame duration
	int jumpCooldown;			//Cooldown counter for jump
	int jumpTimer;				//Counter for jump duration
	bool faceRight;				//Boolean for determining direction hero is facing at rest
	bool inAir;
	bool isAlive;

	float heroJumpSpeed;
	int level_;
	int experience_;

	void walkAnim();			//Animation sequence for walking
	void jump(float seconds);
public:
	Hero();
	void update(float seconds);
	void render(sf::RenderWindow &window);
	void onHit(float dmg);
	void jump();
	void left();
	void right();
	void setCollisionNum(int);
	void setExperience(int add_exp);

	// Accessors
	const float getSpeedX()
	{
		return velocity.x;
	}

	const float getSpeedY()
	{
		return velocity.y;
	}

	const bool getAlive()
	{
		return isAlive;
	}

	const int getHP()
	{
		return HP;
	}

	const int getExperience()
	{ return experience_; }



	sf::Sprite getHeroSprite()
	{
		return Sprite;
	}

	void update();
};

#endif

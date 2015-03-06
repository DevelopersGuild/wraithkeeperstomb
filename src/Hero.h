#ifndef HERO_H
#define HERO_H

#include "Entity.h"
#include "Weapons.h"
#include <SFML/Graphics.hpp>

class Weapons;

class Hero : public Entity
{
private:
	sf::Vector2f velocity;
	sf::Vector2i anim;		//Tracker for hero sprite frames

	float speed;
	float speedMultiplier;
	float armor;
	int collisionNum;
	float HP;
	int xFrame;					//Current frame in the x grid
	int yFrame;					//Current frame in the y grid
	int frameTimer;				//Counter for sprite frame duration
	float jumpCooldown;			//Cooldown counter for jump
	float jumpTimer;				//Counter for jump duration
	bool faceRight;				//Boolean for determining direction hero is facing at rest
	bool inAir;

	float heroJumpSpeed;
	int level_;
	int experience_;

	Weapons * weapon = 0;

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

	void setLevel(int level) { level_ = level; }
	void setHP(int hp) { HP = hp; }

	void giveWeapon(Weapons * weapon);

	// Accessors
	const float getSpeedX()
	{
		return velocity.x;
	}

	const float getSpeedY()
	{
		return velocity.y;
	}

	const int getHP()
	{
		return HP;
	}

	const int getLevel() {
		return level_;
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

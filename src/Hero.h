#ifndef HERO_H
#define HERO_H
#include "Entity.h"

#include <SFML/Graphics.hpp>

class Hero : public Entity
{
private:
	sf::Vector2f velocity;
	sf::Vector2i anim;		//Tracker for hero sprite frames

	int heroHP;
	int xFrame;					//Current frame in the x grid
	int yFrame;					//Current frame in the y grid
	int frameTimer;				//Counter for sprite frame duration
	int jumpCooldown;			//Cooldown counter for jump
	int jumpTimer;				//Counter for jump duration
	bool faceRight;				//Boolean for determining direction hero is facing at rest
	bool isAlive;
	bool inAir;
	float heroSpeed;
	float heroSpeedMultiplier;
	float heroJumpSpeed;

	void walkAnim();			//Animation sequence for walking
	void left();
	void right();
	void jump(float seconds);
public:
	Hero();
	void update(float seconds);
	void render(sf::RenderWindow &window);
	// Accessors
	const float getSpeedX()
	{
		return velocity.x;
	}
	const float getSpeedY()
	{
		return velocity.y;
	}
	void update();
};

#endif

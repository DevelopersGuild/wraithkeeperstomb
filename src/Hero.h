#ifndef HERO_H
#define HERO_H
#include "Entity.h"

#include <SFML/Graphics.hpp>

class Hero : public Entity
{
private:
<<<<<<< HEAD
	sf::Texture heroTexture;
	sf::Sprite heroSprite;
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
	float heroJumpSpeed;// = 80;

	void walkAnim();			//Animation sequence for walking
	void left();
	void right();
	void jump(float seconds);
=======

>>>>>>> 9f8d7c0... Entity
public:
	Hero();
<<<<<<< HEAD
	void update(float seconds);
	void render(sf::RenderWindow& window);

<<<<<<< HEAD
	// Accessors
	const float getX()
	{
		return heroSprite.getPosition().x;
	}
	const float getY()
	{
		return heroSprite.getPosition().y;
	}
	const float getSpeedX()
	{
		return velocity.x;
	}
	const float getSpeedY()
	{
		return velocity.y;
	}
	const sf::FloatRect getCollisionRect()
	{
		return heroSprite.getGlobalBounds();
	}
	const bool getAlive()
	{
		return isAlive;
	}
	const int getHP()
	{
		return heroHP;
	}
=======
>>>>>>> 9f8d7c0... Entity
=======
	void update();
	void onHit(int dmg);
>>>>>>> 3354455... Added/Modified Entity, Hero, Enemies, Enemy1, and Enemy2
};

#endif

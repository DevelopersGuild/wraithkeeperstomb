#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>

class Hero
{
private:
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
	float heroJumpSpeed = 80;

	void walkAnim();			//Animation sequence for walking
	void left();
	void right();
	void jump(float seconds);
public:
	Hero();
	void update(float seconds);
	void render(sf::RenderWindow& window);

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
};

#endif

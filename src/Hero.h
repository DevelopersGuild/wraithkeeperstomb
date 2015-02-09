#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>

class Hero
{
private:
	sf::Texture heroTexture;
	sf::Sprite heroSprite;
	sf::Vector2f velocity;
	sf::Vector2i direct;

	enum Direction { faceRight, faceLeft };

	int heroHP;
	int jumpTimer;
	int jumpCooldown;
	bool isAlive;
	bool inAir;
	float heroSpeed;
	float heroSpeedMultiplier;
	float heroJumpSpeed = 80;

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

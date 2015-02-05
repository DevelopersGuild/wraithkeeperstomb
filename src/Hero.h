#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>

class Hero
{
private:
	sf::Texture heroTexture;
	sf::Sprite heroSprite;

	int heroHP;
	bool isAlive;
	float heroSpeed;
	float heroSpeedMultiplier;

	void jump();
	void left();
	void right();
public:
	Hero();
	void update();
	void render(sf::RenderWindow& window);

	// Accessors
	const float getX()
	{ return heroSprite.getPosition().x; }
	const float getY()
	{ return heroSprite.getPosition().y; }
	const sf::FloatRect getCollisionRect()
	{ return heroSprite.getGlobalBounds(); }
	const bool getAlive()
	{ return isAlive; }
	const int getHP()
	{ return heroHP; }
};

#endif

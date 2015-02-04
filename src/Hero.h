#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>

class Hero
{
private:
	sf::Texture heroTexture;
	sf::Sprite heroSprite;

	int heroHP;
	int heroMP;
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
	const bool getAlive()
	{ return isAlive; }
	const int getHP()
	{ return heroHP; }
	const int getMP()
	{ return heroMP; }
};

#endif

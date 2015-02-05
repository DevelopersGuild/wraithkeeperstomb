#include "Hero.h"
#include "Constants.h"
#include "Physics.h"

Hero::Hero() 
{
	// Load hero texture, assign to sprite, set starting sprite dimensions
	heroTexture.loadFromFile("../assets/sprites/hero.png"); 
	heroSprite.setTexture(heroTexture);
	heroSprite.setOrigin(32, 128);
	heroSprite.setPosition(640, 640);
	
	// Initialize basic hero stats
	heroHP = HERO_BASE_HP;
	isAlive = true;
	heroSpeedMultiplier = 1;
	heroSpeed = HERO_BASE_SPEED * heroSpeedMultiplier;
	
	
}

void Hero::left()
{
	heroSprite.move(-heroSpeed, 0.f);
}

void Hero::right()
{
	heroSprite.move(heroSpeed, 0.f);
}

void Hero::jump()
{
	// not yet written
}

void Hero::update()
{
	// Handle movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		left();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		right();

	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		jump();

	// Check if alive
	if (heroHP <= 0)
		isAlive = false;
}

void Hero::render(sf::RenderWindow &window)
{
	window.draw(heroSprite);
}

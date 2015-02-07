#include "Entity.h"
#include "Hero.h"
#include "Constants.h"

Hero::Hero()
{
	// Load hero texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile("../assets/sprites/hero.png"); 
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128);
	Sprite.setPosition(640, 640);
	
	// Initialize basic hero stats
	HP = HERO_BASE_HP;
	SpeedMultiplier = 1;
	Speed = HERO_BASE_SPEED * SpeedMultiplier;
	isAlive = true;
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
	if (HP <= 0)
		isAlive = false;
}

void Hero::onHit(int dmg)
{
	//armor and stuff
}
#include "Entity.h"
#include "Enemies.h"
#include "Constants.h"

Enemies::Enemies()
{

}

void Enemies::update(Hero* hero)
{
	// Handle movement

	// Detection
	if (heroDetection(hero))
		onHeroDetected(hero);
	// Check if alive
	if (HP <= 0)
		isAlive = false;
}

void Enemies::render(sf::RenderWindow &window)
{
	window.draw(Sprite);
}

void onHeroDetected(Hero* hero)
{

}
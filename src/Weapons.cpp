#include "Weapons.h"
#include "Constants.h"
#include <ctime>

Weapons::Weapons()
{

}

Weapons::~Weapons()
{

}

void Weapons::setPosition(float xPos, float yPos)
{
	Sprite.setPosition(sf::Vector2f(xPos, yPos));
}

float Weapons::dmgRandomizer(float fluctuation)
{
	//returns damage +- fluctuation
	return damage - fluctuation + rand() % (2 * (int)fluctuation + 1);
}

float Weapons::critical(float multiplier)
{
	if (rand() % 100 < crit_chance)
		return multiplier;
	else
		return 1.0;
}

void Weapons::update(Hero *hero, Entity *&enemy)
{
	
}

void Weapons::render(sf::RenderWindow &window)
{
	window.draw(Sprite);
}
#include "Weapons.h"
#include "Constants.h"
#include <ctime>

Weapons::Weapons()
{

}

Weapons::~Weapons()
{

}

float Weapons::dmgRandomizer(float fluctuation)
{//returns damage +- fluctuation
	return damage - fluctuation + rand() % (2 * (int)fluctuation + 1);
}

float Weapons::critical(float multiplier)
{
	if (rand() % 100 < crit_chance)
		return multiplier;
	else
		return 1.0;
}

void Weapons::update(float seconds)
{
	
}

void Weapons::render(sf::RenderWindow &window)
{
	window.draw(WeaponSprite);
}
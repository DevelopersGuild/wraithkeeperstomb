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

const sf::FloatRect Weapons::getAttackRect(bool hero_faceRight)
{
	if (hero_faceRight)
	{
		sf::FloatRect collisionRect(getX(), getY() - 68, range, 32.f);//137 = weapon y-origin
		return collisionRect;
	}
	else
	{
		sf::FloatRect collisionRect(getX(), getY() - 68, -range, 32.f);
		return collisionRect;
	}
}

bool Weapons::attack()
{
	return false;
}

void Weapons::update(bool)
{
	
}

void Weapons::render(sf::RenderWindow &window)
{
	window.draw(Sprite);
}

#include "Powerup.h"
#include "Game.h"
#include "Constants.h"
#include <iostream>

Powerup::Powerup()
{

}

void Powerup::update(float time)
{
	Hero * hero = Game::getHero();
	if (is_alive_ && hero->getCollisionRect().intersects(Sprite.getGlobalBounds()))
	{
		is_alive_ = false;
		apply(hero);
		effectTextAppears();
	}
}

void Powerup::render(sf::RenderWindow &window)
{
	if (is_alive_)
		window.draw(Sprite);
}
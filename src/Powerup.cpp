#include "Powerup.h"
#include "Game.h"
#include "Constants.h"

Powerup::Powerup(float posX, float posY, float sizeX, float sizeY)
{
	Sprite.setOrigin(posX, posY);
	Sprite.setPosition(sizeX, sizeY);
}

void Powerup::update(float time)
{
	Hero * hero = Game::getHero();
	if (is_alive_ && hero->getCollisionRect().intersects(Sprite.getGlobalBounds()))
	{
		is_alive_ = false;
		apply(hero);
	}
	
}

void Powerup::render(sf::RenderWindow &window)
{
	if (is_alive_)
		window.draw(Sprite);
}
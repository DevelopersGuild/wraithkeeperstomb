#include "Levels.h"

Levels::Levels()
{
	// Load background texture and assign to rectangle shape
	bgTexture.loadFromFile("../assets/background.png"); 
	bgRect.setSize(sf::Vector2f(1280,720));	
	bgRect.setTexture(&bgTexture);
}

void Levels::update()
{
	// nothing yet
}

void Levels::render(sf::RenderWindow &window)
{
	window.draw(bgRect);
}

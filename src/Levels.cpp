#include "Levels.h"

Levels::Levels()
{
	// Load background texture and assign to rectangle shape
	bgTexture.loadFromFile("../assets/sprites/background.png"); 
	groundTexture.loadFromFile("../assets/sprites/ground.png");
	bgRect.setSize(sf::Vector2f(2560, 1440));
	bgRect.setTexture(&bgTexture);
	groundRect.setSize(sf::Vector2f(2560, 32));
	groundRect.setTexture(&groundTexture);
	groundRect.setPosition(0, 1340);
}

void Levels::update()
{
	// nothing yet
}

void Levels::render(sf::RenderWindow &window)
{
	window.draw(bgRect);
	window.draw(groundRect);
}

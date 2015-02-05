#include "Levels.h"

Levels::Levels()
{
	// Load background texture and assign to rectangle shape
	bgTexture.loadFromFile("../assets/sprites/background.png"); 
	groundTexture.loadFromFile("../assets/sprites/ground.png");
	bgRect.setSize(sf::Vector2f(1280,720));	
	bgRect.setTexture(&bgTexture); 
	groundRect.setSize(sf::Vector2f(1280, 16));
	groundRect.setTexture(&groundTexture);
	groundRect.setPosition(0, 635);
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

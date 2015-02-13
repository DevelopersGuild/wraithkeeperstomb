#include "Levels.h"

Levels::Levels()
{
	// Load background texture and assign to rectangle shape
	bgTexture.loadFromFile("../assets/sprites/background.png"); 
	groundTexture.loadFromFile("../assets/sprites/GroundTexture.png");
	bgRect.setSize(sf::Vector2f(2560, 1440));
	bgRect.setTexture(&bgTexture);
	bgRect.setTextureRect({ 0, 0, 5500, 3000 });
	groundTexture.setRepeated(true);
	bgTexture.setRepeated(true);
	groundRect.setSize(sf::Vector2f(2560, 64));
	groundRect.setTexture(&groundTexture);
	groundRect.setTextureRect({ 0, 0, 1000, 32 });
	groundRect.setPosition(0, 1340);

	// Create a platform
	platform.setSize(sf::Vector2f(350.f, 50.f));
	platform.setPosition(sf::Vector2f(700.f, 1250.f));
}

void Levels::update()
{
	// nothing yet
}

void Levels::render(sf::RenderWindow &window)
{
	window.draw(bgRect);
	window.draw(groundRect);

	platform.render(window);
}

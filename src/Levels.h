#ifndef LEVELS_H
#define LEVELS_H

#include <SFML/Graphics.hpp>
#include "Platform.h"

class Levels
{
private:
	sf::Texture bgTexture;
	sf::Texture groundTexture;
	sf::RectangleShape bgRect;
	sf::RectangleShape groundRect;
	Platform platform;

public:
	Levels();
	void update();
	void render(sf::RenderWindow &);

	const sf::FloatRect getGroundRect()
	{ return groundRect.getGlobalBounds(); }
};

#endif

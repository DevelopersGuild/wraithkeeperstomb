#ifndef LEVELS_H
#define LEVELS_H

#include <SFML/Graphics.hpp>

class Levels
{
private:
	sf::Texture bgTexture;
	sf::Texture groundTexture;
	sf::RectangleShape bgRect;
	sf::RectangleShape groundRect;
public:
	Levels();
	void update();
	void render(sf::RenderWindow &);

	const sf::FloatRect getGroundRect()
	{ return groundRect.getGlobalBounds(); }
};

#endif

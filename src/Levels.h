#ifndef LEVELS_H
#define LEVELS_H

#include <SFML/Graphics.hpp>

class Levels
{
private:
	sf::RectangleShape bgRect;
	sf::Texture bgTexture;
public:
	Levels();
	void update();
	void render(sf::RenderWindow &);
};

#endif

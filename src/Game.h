#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;
	void render();
	void handleEvent(sf::Event);
public:
	Game();
	void mainLoop();
};

#endif

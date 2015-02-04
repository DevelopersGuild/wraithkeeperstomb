#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Levels.h"
#include "Hero.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;

	Levels levels;
	Hero hero;

	void update();
	void render();
	void handleEvent(sf::Event);
public:
	Game();
	void mainLoop();
};

#endif

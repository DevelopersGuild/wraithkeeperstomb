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
	enum{
		titleScreen, inGame, pause
	}GameState;

	sf::RenderWindow window;
	sf::Event event;

	sf::Font century;
	sf::Text title;
	sf::Text pressEnter;

	Levels levels;
	Hero hero;

	void update();
	void render();
	void handleEvent(sf::Event);
	void loadAssets();
	void collision(sf::RectangleShape, sf::RectangleShape);
	void titleUpdate();
	void gameUpdate();
	void pauseUpdate();
public:
	Game();
	void mainLoop();
};

#endif

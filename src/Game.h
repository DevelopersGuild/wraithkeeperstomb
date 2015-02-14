#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Levels.h"
#include "Hero.h"

class Game
{
private:
	enum{
		titleScreen, inGame, pause, dead
	}GameState;

	sf::RenderWindow window;
	sf::Event event;

	sf::Clock clock;	//Starts the clock
	sf::Time deltaTime;	//Difference in time

	//Camera
	sf::View camera;

	sf::Font blackcastle;
	sf::Font century;
	sf::Text title;
	sf::Text pressEnter;
	sf::Text pauseText;
	sf::Text pressResume;

	Levels levels;

	std::vector<Entity * > entityRegistry;

	void update();
	void render();
	void handleEvent(sf::Event);
	void loadAssets();
	void collision(Hero *, sf::FloatRect);
	void titleUpdate();
	void gameUpdate();
	void pauseUpdate();
	void deathUpdate();

	static Hero * theHero;
public:
	Game();
	void mainLoop();

	static Hero * getHero();
};


#endif

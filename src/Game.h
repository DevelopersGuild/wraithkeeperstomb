#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Levels.h"
#include "Hero.h"
#include "Entity.h"
#include "Enemy1.h"

class Game
{
private:
	enum class GameState {
		titleScreen, inGame, pause, victory, gameOver
	} gameState_;

	sf::RenderWindow window;

	sf::Clock clock;	//Starts the clock
	sf::Time deltaTime;	//Difference in time
	sf::Clock knockBackTime;

	//Camera
	sf::View camera;
	sf::View minimap;


	sf::Font blackcastle;
	sf::Font century;
	sf::Text title;
	sf::Text victoryText;
	sf::Text pressEnter;
	sf::Text pauseText;
	sf::Text pressResume;
    sf::Text youDied;
    sf::Text returnToTitle;

	sf::RectangleShape HPbar;

	Levels levels;

	void update();
	void render();
	void handleEvent(sf::Event &event);
	void loadAssets();
	void collision(Entity *, Platform);
	void titleUpdate();
	void gameUpdate();
	void pauseUpdate();
	void victoryUpdate();
	void gameOverUpdate();
	void hitCollision(Entity *, Entity *);

	static Hero *theHero;

	void CreateEntities();

	void LoadStats();
	void SaveStatsToFile();
public:
	Game();
	void mainLoop();

	static Hero * getHero();

	static std::vector<Entity *> entityRegistry;
};


#endif

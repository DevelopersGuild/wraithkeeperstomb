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

	enum class MenuSwitch {
		continueGame, newGame, loadGame, options, exitGame
	} menuSwitch_;

	sf::RenderWindow window;

	sf::Clock clock;	//Starts the clock
	sf::Time deltaTime;	//Difference in time
	sf::Clock knockBackTime;

	//Camera
	sf::View camera;
	sf::View minimap;

	sf::Font blackcastle;
	sf::Font gothicbold;
	sf::Text title;
	sf::Text victoryText;
	sf::Text continueButton;
	sf::Text continueButtonDisabled;
	sf::Text newGameButton;
	sf::Text loadGameButton;
	sf::Text optionsButton;
	sf::Text exitGameButton;
	sf::Text continueButtonHL;
	sf::Text continueButtonHLDisabled;
	sf::Text newGameButtonHL;
	sf::Text loadGameButtonHL;
	sf::Text optionsButtonHL;
	sf::Text exitGameButtonHL;
	sf::Text pauseText;
	sf::Text pressResume;
    sf::Text youDied;
    sf::Text returnToTitle;

	sf::RectangleShape HPbar;
	sf::RectangleShape MPbar;

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
	bool projectileCollide(Entity *, Projectile *);

	static Hero *theHero;

	void CreateEntities();
	//projectiles
	enum heroProjectileType { holyOrb, thunderOrb } hero_projectile_type;
	enum enemyProjectileType { fireBall, iceBall, thunderBall } enemy_projectile_type;
	std::list<Projectile*> projectiles;//may need to be split in 2 (hero's and enemies')

	void LoadStats();
	void SaveStatsToFile();
public:
	Game();
	~Game();
	void mainLoop();

	static Hero * getHero();

	static std::vector<Entity *> entityRegistry;
};

#endif

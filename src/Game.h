#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <queue>
#include "Levels.h"
#include "Hero.h"
#include "Entity.h"

class Game
{
private:
	enum class GameState {
		titleScreen, inGame, pause, victory, gameOver, enterDoor, dialogueState
	} gameState_;

	enum class MenuSwitch {
		play, exit
	} menuSwitch_;

	sf::RenderWindow window;

	sf::Clock clock;	//Starts the clock
	sf::Time deltaTime;	//Difference in time
	sf::Clock gClock;	//Starts the clock
	sf::Time dTime;	//Difference in time
	sf::Clock knockBackTime;
	float stageLoadingTime;

	//Camera
	sf::View camera;
	sf::View minimap;

	sf::Texture menuTexture;
	sf::Sprite menuSprite;

	sf::Font blackcastle;
	sf::Font gothicbold;
	sf::Font lato;

	sf::Text title;
	sf::Text victoryText;
	sf::Text playButton;
	sf::Text playButtonHL;
	sf::Text exitButton;
	sf::Text exitButtonHL;
	sf::Text pauseText;
	sf::Text pressResume;
    sf::Text youDied;
    sf::Text returnToTitle;
	sf::Text loading;
	sf::Text dmgText;
	sf::Text dialogue;

	sf::RectangleShape HPbar;
	sf::RectangleShape MPbar;
	sf::RectangleShape textBox;

	Levels levels;

	bool doorOpen;

	void update();
	void render();
	void handleEvent(sf::Event &event);
	void loadAssets();
	void collision(Entity *, Platform&);
	void titleUpdate();
	void gameUpdate();
	void enterDoorUpdate();
	void textUpdate();
	void pauseUpdate();
	void victoryUpdate();
	void gameOverUpdate();
	void hitCollision(Entity *, Entity *);
	bool projectileCollide(Entity *, Projectile *);
	void enterDoor(Entity *);

	static Hero *theHero;

	void CreateEntities();
	//projectiles
	enum heroProjectileType { holyOrb, thunderOrb } hero_projectile_type;
	enum enemyProjectileType { fireBall, iceBall, thunderBall } enemy_projectile_type;
	std::list<Projectile*> projectiles;//may need to be split in 2 (hero's and enemies')

	void LoadStats();
	void SaveStatsToFile();
	int cleanupEntities(); //delete dead entities
	void cleanupProjectiles(); //delete overrange projectiles
	void cleanupAll(); //delete all entities and projectiles except hero
	void loadTextLineHL(sf::Text &text, std::string line, int yPos);
	void loadTextLine(sf::Text &text, std::string line, int yPos);
	void loadDialogueBoxAndFont(sf::Text &text);
	void dmgTextAppears(bool isEnemy, float x, float y, int dmg);
	void insertDialogue(int scriptNum);

public:
	Game();
	~Game();
	void mainLoop();

	static Hero * getHero();

	static std::vector<Entity *> entityRegistry;
	std::vector<sf::Text> dmgTextRegistry;
	std::queue<sf::Text> dialogueRegistry;
};

#endif

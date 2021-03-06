#ifndef LEVELS_H
#define LEVELS_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Door.h"
#include "Entity.h"

using LevelNum = int;

class Levels
{
private:
	struct {
		sf::Texture texture;
		sf::RectangleShape rectangle;
	} background_;

	sf::RectangleShape back;

	void createPlatform(int, float, float, float, float);
	void createGround(int, float, float, float, float);

	int level;
	bool isBoss;
	int set_num;
	int platformType; //0 = horizontal, 1 = vertical (wall)
	Door door;

	float bossFightChance;
	int maps_passed;

public:
	std::vector<Platform> platforms;

public:
	Levels();
	//void createEntities();
	void update();
	void render(sf::RenderWindow &);
	void renderPlats(sf::RenderWindow &);
	void platformSets();

	void createEnemy(int/*enemy type*/, float, float, float, float);
	void powerup(int/*power up type*/, float, float);
	void backGroundSets();
	void entitiesSets();
	void doorSets();
	void createBackground();

	void roomGenerater();
	void cleanup();
	void levelup();

	void bossAppearance();
	void incrBossFightChance();

//	const sf::FloatRect getGroundRect()
//	{ return ground_.rectangle.getGlobalBounds(); }
	Door getDoor()
	{ return door; }
	int getLevel()
	{ return level; }
	bool getIsBoss()
	{ return isBoss; }
	bool setDoor(bool status);
};

/*************************************************
*	BackgroundGenerator
*	
*	 Loads a background sprite for given level
*
*************************************************/
class BackgroundGenerator
{
private:
	BackgroundGenerator() {}

	sf::Texture background_texture_;

	std::string GetFileName(LevelNum level_num);

public:
	static BackgroundGenerator& instance()
	{
		static BackgroundGenerator instance_; // initializes only once
		return instance_;
	}

	~BackgroundGenerator() {}

	void LoadTextureForLevelOrDie(LevelNum level);

	const sf::Texture& background_texture() const { return background_texture_; }

};

#endif

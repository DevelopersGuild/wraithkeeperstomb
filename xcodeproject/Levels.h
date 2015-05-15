#ifndef LEVELS_H
#define LEVELS_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Door.h"

using LevelNum = int;

class Levels
{
private:
	struct {
		sf::Texture texture;
		sf::RectangleShape rectangle;
	} background_;

	sf::RectangleShape back;

	void createPlatform(float, float, float, float);

	bool isBoss;
	int l; //level

	Door door;

public:
	std::vector<Platform> platforms;

public:
	Levels();
	void createEntities();
	void update();
	void render(sf::RenderWindow &);
	void renderPlats(sf::RenderWindow &);
	void platformSets();

	void createEnemy(int/*enemy type*/, float, float);
	void powerup(int/*power up type*/, float, float);
	void backGroundSets();
	void entitiesSets();
	void createBackground();

//	const sf::FloatRect getGroundRect()
//	{ return ground_.rectangle.getGlobalBounds(); }
	Door getDoor()
	{ return door; }
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
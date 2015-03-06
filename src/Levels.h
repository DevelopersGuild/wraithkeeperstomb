#ifndef LEVELS_H
#define LEVELS_H

#include <SFML/Graphics.hpp>
#include "Platform.h"

using LevelNum = int;

class Levels
{
private:
	struct {
		sf::Texture texture;
		sf::RectangleShape rectangle;
	} ground_;

	struct
	{
		sf::Texture texture;
		sf::RectangleShape rectangle;
	} background_;

	sf::RectangleShape back;

	void createPlatform(float, float, float, float);

public:
	std::vector<Platform> platforms;

public:
	Levels();
	void createEntities();
	void update();
	void render(sf::RenderWindow &);
	void renderPlats(sf::RenderWindow &);

	const sf::FloatRect getGroundRect()
	{ return ground_.rectangle.getGlobalBounds(); }
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

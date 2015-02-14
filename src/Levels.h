#ifndef LEVELS_H
#define LEVELS_H

#include <SFML/Graphics.hpp>
#include "Platform.h"

class BackgroundGenerator;

using LevelNum = int;

class Levels
{
private:
	sf::Texture bgTexture;
	sf::Texture groundTexture;
	sf::RectangleShape bgRect;
	sf::RectangleShape groundRect;
	struct Background
	{
		sf::Texture texture;
		sf::RectangleShape rectangle;
	} Background;

public:
	Platform platform;

public:
	Levels();
	void update();
	void render(sf::RenderWindow &);


	const sf::FloatRect getGroundRect()
	{ return groundRect.getGlobalBounds(); }
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
		static BackgroundGenerator *instance_ = new BackgroundGenerator(); // initializes only once
		return *instance_;
	}

	~BackgroundGenerator() {}

	void LoadTextureForLevelOrDie(LevelNum level);

	const sf::Texture& background_texture() const { return background_texture_; }

};

#endif

#include "Levels.h"
#include "Powerup.h"
#include "Enemy1.h"
#include "Enemy2.h"

#include <vector>

Levels::Levels()
{
	// Load background texture and assign to rectangle shape
	BackgroundGenerator::instance().LoadTextureForLevelOrDie(2); // current level 1; just testing

	background_.texture = BackgroundGenerator::instance().background_texture(); // assign the texture
	background_.texture.setRepeated(true);
	background_.rectangle.setSize(sf::Vector2f(2560, 1440));
	background_.rectangle.setTexture(&background_.texture);
	background_.rectangle.setTextureRect({ 0, 0, 1200, 600 });

	ground_.texture.loadFromFile("../assets/sprites/GroundTexture.png");
	ground_.texture.setRepeated(true);
	ground_.rectangle.setSize(sf::Vector2f(2560, 64));
	ground_.rectangle.setTexture(&ground_.texture);
	ground_.rectangle.setTextureRect({ 0, 0, 1000, 32 });													   
	ground_.rectangle.setPosition(0, 1340);

	//Minimap Background
	back.setSize(sf::Vector2f(2560, 1440));
	back.setFillColor(sf::Color::Color(0, 0, 0, 150));
	

	createPlatform(500.f, 900.f,350.f, 50.f);

	createPlatform(1000.f, 910.f, 40.f, 60.f);

	createPlatform(1230.f, 890.f, 56.f, 52.f);

	createPlatform(1450.f, 920.f, 49.f, 53.f);

	createPlatform(700.f, 1100.f, 350.f, 50.f);


}

void Levels::createEntities()
{
	Entity * e = new Enemy2;
	Game::entityRegistry.push_back(e);

	e = new PowerupCookie;
	e->setPosition(500.f, 800.f);
	Game::entityRegistry.push_back(e);

	e = new PowerupSpear;
	e->setPosition(800.f, 800.f);
	Game::entityRegistry.push_back(e);
}

void Levels::createPlatform(float posX, float posY, float sizeX, float sizeY)
{
	Platform pl;
	pl.setSize(sf::Vector2f(sizeX, sizeY));
	pl.setPosition(sf::Vector2f(posX, posY));
	pl.setTexture();
	platforms.emplace_back(pl);
}

void Levels::update()
{
	// nothing yet
}

void Levels::render(sf::RenderWindow &window)
{
	window.draw(background_.rectangle);
	window.draw(ground_.rectangle);
	for (size_t i = 0; i < platforms.size(); i++)
	{
		platforms[i].render(window);
	}
}

//renders minimap
void Levels::renderPlats(sf::RenderWindow &window){
	window.draw(back);
	window.draw(ground_.rectangle);
	for (size_t i = 0; i < platforms.size(); i++)
	{
		platforms[i].render(window);
	}
}


std::string BackgroundGenerator::GetFileName(LevelNum level_num)
{
	std::string filename;
	switch (level_num)
	{
	case 1: return filename = "../assets/sprites/background.png";
	case 2: return filename = "../assets/sprites/background2.png";
	default: return filename; // it is "" when initialized
		break;
	}
}

void BackgroundGenerator::LoadTextureForLevelOrDie(LevelNum level)
{
	std::string filetoload = this->GetFileName(level);
	if (filetoload != "") {
		background_texture_.loadFromFile(filetoload);
	}
	else {
		return; // TODO: notify about dying
		// throw "Cannot load the texture!";
	}
}

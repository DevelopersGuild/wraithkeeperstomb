#include "Levels.h"

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

	// Create a platform
	platform.setSize(sf::Vector2f(350.f, 50.f));
	platform.setPosition(sf::Vector2f(700.f, 1100.f));
}

void Levels::update()
{
	// nothing yet
}

void Levels::render(sf::RenderWindow &window)
{
	window.draw(background_.rectangle);
	window.draw(ground_.rectangle);
	platform.render(window);
}

//renders minimap
void Levels::renderPlats(sf::RenderWindow &window){
	window.draw(back);
	window.draw(ground_.rectangle);
	platform.render(window);
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

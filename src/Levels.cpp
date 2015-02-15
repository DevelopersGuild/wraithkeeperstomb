#include "Levels.h"

Levels::Levels()
{
	// Load background texture and assign to rectangle shape
	BackgroundGenerator::instance().LoadTextureForLevelOrDie(1); // current level 1; just testing

	Background.texture = BackgroundGenerator::instance().background_texture(); // assign the texture
	Background.texture.setRepeated(true);
	Background.rectangle.setSize(sf::Vector2f(2560, 1440));
	Background.rectangle.setTexture(&Background.texture);
	Background.rectangle.setTextureRect({ 0, 0, 5500, 3000 });

	groundTexture.loadFromFile("../assets/sprites/GroundTexture.png");
	groundTexture.setRepeated(true);
	groundRect.setSize(sf::Vector2f(2560, 64));
	groundRect.setTexture(&groundTexture);
	groundRect.setTextureRect({ 0, 0, 1000, 32 });
	groundRect.setPosition(0, 1340);

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
	window.draw(Background.rectangle);
	//window.draw(bgRect);
	window.draw(groundRect);
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

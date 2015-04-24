#include "Levels.h"
#include "Powerup.h"
#include "EnemyMage.h"
#include "EnemyReaper.h"

#include <vector>

Levels::Levels()
{
	backGroundSets(2);
	//// Load background texture and assign to rectangle shape
	//BackgroundGenerator::instance().LoadTextureForLevelOrDie(2); // current level 1; just testing

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
	

	platformSets(5);

}

void Levels::entitiesSets(int l)
{
	switch (l)
	{
	case 1:
		createEnemy(1, 700.f, 1360.f);
		createEnemy(1, 800.f, 1360.f);
		powerup(1, 500.f, 1200.f);
		powerup(2, 800.f, 800.f);
		break;
	case 2:
		createEnemy(1, 700.f, 1360.f);
		createEnemy(2, 800.f, 1360.f);
		powerup(1, 500.f, 1200.f);
		powerup(2, 700.f, 1100.f);
		break;
	case 3:
		createEnemy(2, 600.f, 1360.f);
		createEnemy(2, 779.f, 1360.f);
		powerup(1, 800.f, 850.f);
		powerup(2, 1000.f, 1000.f);
		break;
	default:
		createEnemy(2, 600.f, 1360.f);
		createEnemy(2, 700.f, 1360.f);
		createEnemy(1, 1000.f, 1360.f);
		break;
	}
}

void Levels::createEnemy(int t/*enemy type*/, float x, float y)
{
	Entity *e;
	switch (t)
	{
	case 1:
		e = new EnemyMage;
		e->setPosition(x, y);
		Game::entityRegistry.push_back(e);
		break;
	case 2:
		e = new EnemyReaper;
		e->setPosition(x, y);
		Game::entityRegistry.push_back(e);
		break;
	default:
		return;
	}
}

void Levels::powerup(int t, float x, float y)
{
	Entity *e;
	switch (t)
	{
	case 1:
		e = new PowerupCookie;
		e->setPosition(x, y);
		Game::entityRegistry.push_back(e);
		break;
	case 2:
		e = new PowerupSpear;
		e->setPosition(x, y);
		Game::entityRegistry.push_back(e);
		break;
	default:
		return;
	}
}


void Levels::createEntities()
{
	Entity * e = new EnemyMage;
	e->setPosition(1280.f, 1360.f);
	dynamic_cast<EnemyMage*> (e)->set_patrol_origin(1280.f);
	Game::entityRegistry.push_back(e);

	e = new EnemyReaper;
	e->setPosition(1000.f, 1360.f);
	dynamic_cast<EnemyReaper*> (e)->set_patrol_origin(1000.f);
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

void Levels::platformSets(int sets)
{
	switch (sets)
	{
	case 1:
		createPlatform(500.f, 900.f, 350.f, 32.f);
		createPlatform(1000.f, 910.f, 50.f, 32.f);
		createPlatform(1230.f, 890.f, 50.f, 32.f);
		createPlatform(1400.f, 920.f, 50.f, 32.f);
		createPlatform(700.f, 1100.f, 350.f, 32.f);
		break;
	case 2:
		createPlatform(700.f, 1100.f, 350.f, 32.f);
		createPlatform(1550.f, 1100.f, 100.f, 32.f);
		createPlatform(1550.f, 800.f, 100.f, 32.f);
		createPlatform(1550.f, 600.f, 100.f, 32.f);
		break;
	case 3:
		createPlatform(1200.f, 850.f, 200.f, 32.f);
		createPlatform(1000.f, 1000.f, 600.f, 32.f);
		createPlatform(800.f, 850.f, 200.f, 32.f);
		createPlatform(600.f, 1100.f, 200.f, 32.f);
		break;
	case 4:
		createPlatform(1200.f, 1100.f, 200.f, 32.f);
		createPlatform(1000.f, 900.f, 200.f, 32.f);
		createPlatform(800.f, 1200.f, 200.f, 32.f);
		createPlatform(600.f, 1100.f, 200.f, 32.f);
		createPlatform(1400.f, 800.f, 200.f, 32.f);
		break;
	case 5:
		createPlatform(1400.f, 1100.f, 300.f, 32.f);
		createPlatform(1400.f, 750.f, 300.f, 32.f);
		createPlatform(600.f, 1100.f, 300.f, 32.f);
		createPlatform(600.f, 750.f, 300.f, 32.f);
		createPlatform(1000.f, 900.f, 300.f, 32.f);
		break;
	}
}

void Levels::backGroundSets(int level)
{
	switch (level)
	{
	case 1:
		BackgroundGenerator::instance().LoadTextureForLevelOrDie(1);
		break;
	case 2:
		BackgroundGenerator::instance().LoadTextureForLevelOrDie(2);
		break;
	case 3:
		BackgroundGenerator::instance().LoadTextureForLevelOrDie(3);
		break;
	case 4:
		BackgroundGenerator::instance().LoadTextureForLevelOrDie(4);
		break;
	case 5:
		BackgroundGenerator::instance().LoadTextureForLevelOrDie(5);
		break;
	default:
		BackgroundGenerator::instance().LoadTextureForLevelOrDie(1);
		break;
	}
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
	case 2: return filename = "../assets/sprites/dungeonwindow.png";//background2.png";
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

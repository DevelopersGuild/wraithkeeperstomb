#include "Levels.h"
#include "Powerup.h"
#include "EnemyMage.h"
#include "EnemyReaper.h"
#include "FirstBoss.h"
#include "Paths.h"

#include <vector>

Levels::Levels()
{
	isBoss = false;
	
	srand(time(0));
}

void Levels::cleanup()
{
	platforms.clear();
}

void Levels::roomGenerater()
{
	l = rand() % 5 + 1;
	createBackground();
	door.setTexture(0); //close door
	door.setPosition(2000, 1210);
	//platformSets();
	entitiesSets();
}

void Levels::createBackground()
{
	backGroundSets();
	//// Load background texture and assign to rectangle shape
	//BackgroundGenerator::instance().LoadTextureForLevelOrDie(2); // current level 1; just testing

	background_.texture = BackgroundGenerator::instance().background_texture(); // assign the texture
	background_.texture.setRepeated(true);
	background_.rectangle.setSize(sf::Vector2f(2560, 1440));
	background_.rectangle.setTexture(&background_.texture);
	background_.rectangle.setTextureRect({ 0, 0, 1200, 600 });

	//Minimap Background
	back.setSize(sf::Vector2f(2560, 1440));
	back.setFillColor(sf::Color::Color(0, 0, 0, 150));

	platformSets();
    
}

void Levels::entitiesSets()
{
	if (!isBoss)
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
	else
	{

	}
}

void Levels::createEnemy(int t/*enemy type*/, float x, float y)
{
	Entity *e;
	if (!isBoss)
		switch (t)
		{
		case 1:
			e = new EnemyMage;
			e->setPosition(x, y);
			dynamic_cast<EnemyMage*> (e)->set_patrol_origin(x);
			Game::entityRegistry.push_back(e);
			break;
		case 2:
			e = new EnemyReaper;
			e->setPosition(x, y);
			dynamic_cast<EnemyReaper*> (e)->set_patrol_origin(x);
			Game::entityRegistry.push_back(e);
			break;
		default:
			return;
		}
	else
	{
		e = new FirstBoss;
		e->setPosition(x, y);
		Game::entityRegistry.push_back(e);
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


//void Levels::createEntities()
//{
//	Entity * e = new EnemyMage;
//	e->setPosition(1280.f, 1360.f);
//	dynamic_cast<EnemyMage*> (e)->set_patrol_origin(1280.f);
//	Game::entityRegistry.push_back(e);
//
//	e = new EnemyReaper;
//	e->setPosition(1000.f, 1360.f);
//	dynamic_cast<EnemyReaper*> (e)->set_patrol_origin(1000.f);
//	Game::entityRegistry.push_back(e);
//
//	e = new PowerupCookie;
//	e->setPosition(500.f, 800.f);
//	Game::entityRegistry.push_back(e);
//
//	e = new PowerupSpear;
//	e->setPosition(800.f, 800.f);
//	Game::entityRegistry.push_back(e);
//}

void Levels::createPlatform(int type, float posX, float posY, float sizeX, float sizeY)
{
	Platform pl;
	pl.setSize(sf::Vector2f(sizeX, sizeY));
	pl.setPosition(sf::Vector2f(posX, posY));
	pl.setTexture(type); //type: platform (0) or wall (1) texture
	platforms.push_back(pl);
}

void Levels::platformSets()
{
	switch (l)
	{
	case 1:
		createPlatform(0, 500.f, 900.f, 350.f, 32.f);
		createPlatform(0, 1000.f, 910.f, 50.f, 32.f);
		createPlatform(0, 1230.f, 890.f, 50.f, 32.f);
		createPlatform(0, 1400.f, 920.f, 50.f, 32.f);
		createPlatform(0, 700.f, 1100.f, 350.f, 32.f);
		createPlatform(1, 275.f, 0.f, 32.f, 1440.f);
		createPlatform(1, 2284.f, 0.f, 32.f, 1440.f);
		// Ground Platform
		createPlatform(3, 0.f, GROUND_HEIGHT, 2560.f, 89.f);
		break;
	case 2:
		createPlatform(0, 700.f, 1100.f, 350.f, 32.f);
		createPlatform(0, 1550.f, 1100.f, 100.f, 32.f);
		createPlatform(0, 1550.f, 800.f, 100.f, 32.f);
		createPlatform(0, 1550.f, 600.f, 100.f, 32.f);
		createPlatform(1, 275.f, 0.f, 32.f, 1440.f);
		createPlatform(1, 2284.f, 0.f, 32.f, 1440.f);
		// Ground Platform
		createPlatform(3, 0.f, GROUND_HEIGHT, 2560.f, 89.f);
		break;
	case 3:
		createPlatform(0, 1200.f, 850.f, 200.f, 32.f);
		createPlatform(0, 1000.f, 1000.f, 600.f, 32.f);
		createPlatform(0, 800.f, 850.f, 200.f, 32.f);
		createPlatform(0, 600.f, 1100.f, 200.f, 32.f);
		createPlatform(1, 275.f, 0.f, 32.f, 1440.f);
		createPlatform(1, 2284.f, 0.f, 32.f, 1440.f);
		// Ground Platform
		createPlatform(3, 0.f, GROUND_HEIGHT, 2560.f, 89.f);
		break;
	case 4:
		createPlatform(0, 1200.f, 1100.f, 200.f, 32.f);
		createPlatform(0, 1000.f, 900.f, 200.f, 32.f);
		createPlatform(0, 800.f, 1200.f, 200.f, 32.f);
		createPlatform(0, 600.f, 1100.f, 200.f, 32.f);
		createPlatform(0, 1400.f, 800.f, 200.f, 32.f);
		createPlatform(1, 275.f, 0.f, 32.f, 1440.f);
		createPlatform(1, 2284.f, 0.f, 32.f, 1440.f);
		// Ground Platform
		createPlatform(3, 0.f, GROUND_HEIGHT, 2560.f, 89.f);
		break;
	case 5:
		createPlatform(0, 1400.f, 1100.f, 300.f, 32.f);
		createPlatform(0, 1400.f, 750.f, 300.f, 32.f);
		createPlatform(0, 600.f, 1100.f, 300.f, 32.f);
		createPlatform(0, 600.f, 750.f, 300.f, 32.f);
		createPlatform(0, 1000.f, 900.f, 300.f, 32.f);
		createPlatform(1, 275.f, 0.f, 32.f, 1440.f);
		createPlatform(1, 2284.f, 0.f, 32.f, 1440.f);
		// Ground Platform
		createPlatform(3, 0.f, GROUND_HEIGHT, 2560.f, 89.f);
		break;
	}
}

void Levels::backGroundSets()
{
	switch (2)
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
//	window.draw(ground_.rectangle);
	window.draw(door.getSprite());

	for (size_t i = 0; i < platforms.size(); i++)
	{
		platforms[i].render(window);
	}
}

//renders minimap
void Levels::renderPlats(sf::RenderWindow &window){
	window.draw(back);
    
//	window.draw(ground_.rectangle);
	window.draw(door.getSprite());

	for (size_t i = 0; i < platforms.size(); i++)
	{
		platforms[i].render(window);
	}
}


std::string BackgroundGenerator::GetFileName(LevelNum level_num)
{
	std::string filename;
	switch (2)
	{
	case 1: return filename = resourcePath() + "assets/sprites/background.png";
	case 2: return filename = resourcePath() + "assets/sprites/dungeonwindow.png";
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

bool Levels::setDoor(bool status)
{
	door.setTexture(status);
	return status; //0 = closed, 1 = open
}
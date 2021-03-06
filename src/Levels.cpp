#include "Levels.h"
#include "Powerup.h"
#include "EnemyMage.h"
#include "EnemyReaper.h"
#include "FirstBoss.h"
#include "Paths.h"

#include <vector>
#include <iostream>

Levels::Levels()
{
	isBoss = false;
	bossFightChance = 0;
	level = 1;
	maps_passed = 0;
	srand(time(0));
}

void Levels::levelup()
{
	level++;
	bossFightChance = 0;
	isBoss = false;
}

void Levels::incrBossFightChance()
{
	int incr = (level - 1) * 2.7;
	if (bossFightChance < 90)
		bossFightChance = bossFightChance + 18.f - incr;
	else
		bossFightChance = 90;
}

void Levels::bossAppearance()
{
	if (rand() % 100 < bossFightChance && maps_passed > level * 2)
		isBoss = true;
}

void Levels::cleanup()
{
	platforms.clear();
}

void Levels::roomGenerater()
{
	set_num = rand() % 5 + 1;
	createBackground();
	//platformSets();
	entitiesSets();
	maps_passed++;
}

void Levels::createBackground()
{
	backGroundSets();
	//// Load background texture and assign to rectangle shape
	//BackgroundGenerator::instance().LoadTextureForLevelOrDie(2); // current level 1; just testing
	if (!isBoss) {
		background_.texture = BackgroundGenerator::instance().background_texture(); // assign the texture
		background_.texture.setRepeated(true);
		background_.rectangle.setSize(sf::Vector2f(2560, 1440));
		background_.rectangle.setTexture(&background_.texture);
		background_.rectangle.setTextureRect({ 0, 0, 1200, 600 });
	}
	else {
		background_.texture = BackgroundGenerator::instance().background_texture(); // assign the texture
		background_.texture.setRepeated(true);
		background_.rectangle.setSize(sf::Vector2f(2560, 1440));
		background_.rectangle.setTexture(&background_.texture);
		background_.rectangle.setTextureRect({ 0, 0, 1200, 600 });
	}

	//Minimap Background
	back.setSize(sf::Vector2f(2560, 1440));
	back.setFillColor(sf::Color::Color(0, 0, 0, 150));

	platformSets();
	door.setTexture(0); //close door
	doorSets();
}

void Levels::doorSets()
{
	if (!isBoss)
	{
		switch (set_num)
		{
		case 1:	door.setPosition(1100.f, 600.f - 155.f); break;
		case 2:	door.setPosition(2000.f, 1205.f); break;
		case 3: door.setPosition(650.f, 1205.f); break;
		default: door.setPosition(2000.f, 1205.f); break;
		}
	}
	else
	{
		switch (level)
		{
		case 1:
			door.setPosition(2000.f, 1205.f);
			break;
		default:
			door.setPosition(2000.f, 1205.f);
			break;
		}
	}
}

void Levels::entitiesSets()
{
	if (!isBoss)
		switch (set_num)
	{
		case 1:
			createEnemy(1, 300.f, 749.f, 300.f, 300.f + 450.f);
			createEnemy(1, 300.f, 949.f, 300.f, 300.f + 500.f);
			createEnemy(1, 1200.f, 1150.f, 1300.f, 1300.f + 500.f);
			createEnemy(1, 1800.f, GROUND_HEIGHT, 0.f, 2560.f);
			powerup(1, 1000.f, GROUND_HEIGHT - 50.f);
			powerup(2, 800.f, 850.f);
			break;
		case 2:
			createEnemy(1, 1850.f, GROUND_HEIGHT - 200.f, 1850.f, 1900.f);
			createEnemy(1, 500.f, 1160.f, 500.f, 500.f + 1000.f);
			createEnemy(1, 500.f, 1160.f, 500.f, 500.f + 1000.f);
			createEnemy(2, 900.f, 955.f, 900.f, 900.f + 800.f);
			createEnemy(2, 1850.f, 955.f, 1850.f, 710.f);
			powerup(1, 2100.f, 760.f);
			powerup(2, 2200.f, 760.f);
			break;
		case 3:
			createEnemy(2, 1600.f, 1340.f, 0.f, 2560.f);
			createEnemy(2, 1779.f, 1340.f, 0.f, 2560.f);
			powerup(1, 800.f, 850.f);
			powerup(2, 1000.f, 1000.f);
			break;
		default:
			createEnemy(2, 1600.f, 1340.f, 0.f, 2560.f);
			createEnemy(2, 1700.f, 1340.f, 0.f, 2560.f);
			createEnemy(1, 1000.f, 1360.f, 0.f, 2560.f);
			break;
	}
	else
	{
		switch (level)
		{
		case 1:
			createEnemy(0, 1500.f, 1360.f, 0.f, 2560.f);
			powerup(1, 1200.f, 1100.f);
			break;
		default:
			createEnemy(0, 1500.f, 1360.f, 0.f, 2560.f);
			powerup(1, 1200.f, 1100.f);
			break;
		}
	}
}

void Levels::createEnemy(int t/*enemy type*/, float x, float y, float left_bound, float right_bound)
{
	Entity *e;
	if (!isBoss)
		switch (t)
	{
		case 1:
			e = new EnemyMage;
			e->setPosition(x, y);
			dynamic_cast<EnemyMage*> (e)->set_patrol_origin(x);
			dynamic_cast<EnemyMage*> (e)->setPatrolBoundary(left_bound + 10.f, right_bound - 10.f);
			Game::entityRegistry.push_back(e);
			break;
		case 2:
			e = new EnemyReaper;
			e->setPosition(x, y);
			dynamic_cast<EnemyReaper*> (e)->set_patrol_origin(x);
			dynamic_cast<EnemyReaper*> (e)->setPatrolBoundary(left_bound + 10.f, right_bound - 10.f);
			Game::entityRegistry.push_back(e);
			break;
		default:
			return;
	}
	else
	{
		switch (level)
		{
		case 1:
			e = new FirstBoss;
			e->setPosition(x, y);
			Game::entityRegistry.push_back(e);
			break;
		default:
			e = new FirstBoss;
			e->setPosition(x, y);
			Game::entityRegistry.push_back(e);
			break;
		}
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
	if (!isBoss)
		switch (set_num)
		{
		case 1:
			//createPlatform(0, 500.f, 900.f, 350.f, 32.f);
			createPlatform(0, 1100.f, 600.f, 125.f, 32.f);
			createPlatform(0, 0.f, 750.f, 1000.f, 32.f);
			createPlatform(0, 0.f, 950.f, 1400.f, 32.f);
			createPlatform(0, 900.f, 1150.f, 1660.f, 32.f);
			createPlatform(2, 275.f, 0.f, 32.f, 1440.f);
			createPlatform(2, 2284.f, 0.f, 32.f, 1440.f);
			// Ground Platform
			createPlatform(3, 0.f, GROUND_HEIGHT, 2560.f, 89.f);
			break;
		case 2:
			createPlatform(0, 1850.f, GROUND_HEIGHT - 200.f, 50.f, 160.f);
			createPlatform(0, 0.f, 1160.f, 1500.f, 32.f);
			createPlatform(0, 900.f, 960.f, 800.f, 32.f);
			createPlatform(0, 1850.f, 960.f, 710.f, 32.f);
			createPlatform(0, 2000.f, 760.f, 660.f, 32.f);
			createPlatform(2, 275.f, 0.f, 32.f, 1440.f);
			createPlatform(2, 2284.f, 0.f, 32.f, 1440.f);
			// Ground Platform
			createPlatform(3, 0.f, GROUND_HEIGHT, 2560.f, 89.f);
			break;
		case 3:
			createPlatform(0, 1200.f, 850.f, 200.f, 32.f);
			createPlatform(0, 1000.f, 1000.f, 600.f, 32.f);
			createPlatform(0, 800.f, 850.f, 200.f, 32.f);
			createPlatform(0, 600.f, 1100.f, 200.f, 32.f);
			createPlatform(2, 275.f, 0.f, 32.f, 1440.f);
			createPlatform(2, 2284.f, 0.f, 32.f, 1440.f);
			// Ground Platform
			createPlatform(3, 0.f, GROUND_HEIGHT, 2560.f, 89.f);
			break;
		case 4:
			createPlatform(0, 1200.f, 1100.f, 200.f, 32.f);
			createPlatform(0, 1000.f, 900.f, 200.f, 32.f);
			createPlatform(0, 800.f, 1200.f, 200.f, 32.f);
			createPlatform(0, 600.f, 1100.f, 200.f, 32.f);
			createPlatform(0, 1400.f, 800.f, 200.f, 32.f);
			createPlatform(2, 275.f, 0.f, 32.5f, 1440.f);
			createPlatform(2, 2284.f, 0.f, 32.f, 1440.f);
			// Ground Platform
			createPlatform(3, 0.f, GROUND_HEIGHT, 2560.f, 89.f);
			break;
		case 5:
			createPlatform(0, 1400.f, 1100.f, 300.f, 32.f);
			createPlatform(0, 1400.f, 750.f, 300.f, 32.f);
			createPlatform(0, 600.f, 1100.f, 300.f, 32.f);
			createPlatform(0, 600.f, 750.f, 300.f, 32.f);
			createPlatform(0, 1000.f, 900.f, 300.f, 32.f);
			createPlatform(2, 275.f, 0.f, 32.f, 1440.f);
			createPlatform(2, 2284.f, 0.f, 32.f, 1440.f);
			// Ground Platform
			createPlatform(3, 0.f, GROUND_HEIGHT, 2560.f, 89.f);
			break;
		}
	else
	{
		switch (level)
		{
		case 1:
			createPlatform(0, 1000.f, 1100.f, 700.f, 32.f);
			createPlatform(2, 275.f, 0.f, 32.f, 1440.f);
			createPlatform(2, 2284.f, 0.f, 32.f, 1440.f);
			// Ground Platform
			createPlatform(2, 0.f, GROUND_HEIGHT, 2560.f, 64.f);
			break;
		default:
			createPlatform(0, 1000.f, 1100.f, 700.f, 32.f);
			createPlatform(2, 275.f, 0.f, 32.f, 1440.f);
			createPlatform(2, 2284.f, 0.f, 32.f, 1440.f);
			// Ground Platform
			createPlatform(2, 0.f, GROUND_HEIGHT, 2560.f, 64.f);
			break;
		}
	}
}

void Levels::backGroundSets()
{
	if (!isBoss)
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
	else
	{
		switch (level)
		{
		case 1:
			BackgroundGenerator::instance().LoadTextureForLevelOrDie(6);
			break;
		default:
			BackgroundGenerator::instance().LoadTextureForLevelOrDie(6);
			break;
		}	
	}
}

void Levels::update()
{
	
}

void Levels::render(sf::RenderWindow &window)
{
	window.draw(background_.rectangle);
//	window.draw(ground_.rectangle);

	for (size_t i = 0; i < platforms.size(); i++)
	{
		platforms[i].render(window);
	}
	window.draw(door.getSprite());
	
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
	switch (level_num)
	{
	case 1: /*return filename = resourcePath() + "assets/sprites/background.png";*/
	case 2: 
	case 3:
	case 4:
	case 5: return filename = resourcePath() + "assets/sprites/dungeonwindow.png";
	case 6: return filename = resourcePath() + "assets/sprites/boss_bg.png";
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
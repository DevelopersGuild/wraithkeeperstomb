#include <fstream>
#include <iostream>


#include "Game.h"
#include "Constants.h"
#include "EntityPhysics.h"

std::vector<Entity *> Game::entityRegistry;

Game::Game()
{
	// Create game render window
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chamber's Labyrinth");
	window.setMouseCursorVisible(true);
	window.setKeyRepeatEnabled(false);

	// Limit framerate to 60 and enable Vsync
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	loadAssets();

	GameState = titleScreen;


	CreateEntities();
	LoadStats();

	minimap.setSize(1280, 720);
	minimap.setCenter(1280, 720);

	camera.setCenter(710, theHero->getY() - 100);

	knockBackTime.restart();
}

void Game::CreateEntities()
{
	entityRegistry.clear();

	theHero = new Hero;
	entityRegistry.push_back(theHero);

	levels.createEntities();
}

void Game::mainLoop()
{
	// Main loop
	while (window.isOpen())
	{

		
		// Event loop
		while (window.pollEvent(event))
			handleEvent(event);
		if (GameState == titleScreen)
			titleUpdate();
		else if (GameState == inGame){
			gameUpdate();
			}
		else if (GameState == pause)
			pauseUpdate();
		else if (GameState == victory)
			victoryUpdate();
		else if (GameState == gameOver)
			gameOverUpdate();
		render();
	}
}

void Game::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::Closed)
		window.close();

	// Binds escape to close the window
	if (sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape) {
			SaveStatsToFile();
			window.close();
		}

	// GameState handling
	if (GameState == titleScreen)
	{
		// Keys being pressed in menu
		if (sf::Event::KeyPressed)
		{
			// Specifically if space is pressed
			if (event.key.code == sf::Keyboard::Return)
			{
				// Move to inGame (start playing)
				GameState = inGame;
			}
		}
	}
	if (GameState == inGame)
	{
		// Keys being pressed during gameplay
		if (sf::Event::KeyPressed)
		{
			// Specifically if P is pressed
			if (event.key.code == sf::Keyboard::P)
			{
				// Move to pause
				GameState = pause;
			}
		}
	}
	if (GameState == pause)
	{
		// Keys being pressed during pause screen
		if (sf::Event::KeyPressed)
		{
			// Specifically if R is pressed
			if (event.key.code == sf::Keyboard::R)
			{
				// Move to inGame (resume playing)
				GameState = inGame;
			}
		}
	}
	if (GameState == gameOver)
	{
		// Keys being pressed during dead screen
		if (sf::Event::KeyPressed)
		{
			// Specifically if Enter is pressed
			if (event.key.code == sf::Keyboard::Return)
			{
				
				for (auto &it : entityRegistry) {
					delete it;
				}

				CreateEntities();

                // Move to inGame (resume playing)
				GameState = titleScreen;
				camera.setCenter(500, 500);
				//camera.setCenter(theHero->getX(), theHero->getY());
			}
		}
	}
}


void Game::collision(Entity *hero, Platform plat){
	//Affected area
	sf::FloatRect wallBounds = plat.getCollisionRect();
	sf::FloatRect area;
	if (hero->getCollisionRect().intersects(wallBounds, area))
	{
		// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
		if (area.width > area.height)
		{
			if (area.contains({ area.left, wallBounds.top}))
				
			{
				hero->setPosition(hero->getX(), hero->getY() - area.height + 12);

				// Down side crash 
				hero->setCollisionState(0);
				hero->setGround(&plat);
			}
			else
			{
				//Up side crash
				hero->setPosition(hero->getX(), hero->getY() + area.height);
				hero->setCollisionState(2);
			}
			
		}
		else if (area.width < area.height)
		{
			
			if (hero->getX()<wallBounds.left)
			{
				//Right side crash
				
				hero->setPosition(hero->getX() - area.width, hero->getY());
				
			}
			else
			{
				//Left side crash

				hero->setPosition(hero->getX() + area.width, hero->getY());
				
			}
		}
	}
}

void Game::hitCollision(Entity *getsHit, Entity *hitter)
{

	if ((dynamic_cast<Enemies*>(hitter) || dynamic_cast<Hero*>(hitter)) && getsHit->getCollisionRect().intersects(hitter->getDamagingRect()))
	{
		getsHit->onHit(hitter->getDamage());
		if (knockBackTime.getElapsedTime().asMilliseconds() > 300)
		{
			getsHit->knockBack(hitter);
			
			knockBackTime.restart();
		}
		hitter->freeze();
	}

}

void Game::loadAssets()
{
	century.loadFromFile("../assets/fonts/century.ttf");
	blackcastle.loadFromFile("../assets/fonts/blackcastle.ttf");

	HPbar.setSize(sf::Vector2f(150, 6));
	HPbar.setOutlineColor(sf::Color::White);
	HPbar.setFillColor(sf::Color::Green);
	HPbar.setOutlineThickness(1.5);
	HPbar.setOrigin(0, 6);
	HPbar.setPosition(camera.getCenter().x - 300, camera.getCenter().y- 580);

	title.setFont(blackcastle);
	title.setString("Chamber's Labyrinth");
	title.setCharacterSize(100);
	title.setColor(sf::Color::White);
	title.setPosition(280, 225);

	pressEnter.setFont(century);
	pressEnter.setString("Press Enter to Begin");
	pressEnter.setCharacterSize(48);
	pressEnter.setColor(sf::Color::White);
	pressEnter.setPosition(420, 425);

	victoryText.setFont(century);
	victoryText.setString("Victory!");
	victoryText.setCharacterSize(100);
	victoryText.setColor(sf::Color::White);
	victoryText.setPosition(480, 225);

	pauseText.setFont(century);
	pauseText.setString("Game Paused");
	pauseText.setCharacterSize(100);
	pauseText.setColor(sf::Color::White);
	pauseText.setPosition(280, 225);

	pressResume.setFont(century);
	pressResume.setString("Press R to Resume");
	pressResume.setCharacterSize(48);
	pressResume.setColor(sf::Color::White);
	pressResume.setPosition(420, 425);
    
    youDied.setFont(century);
    youDied.setString("YOU DIED");
    youDied.setCharacterSize((200));
    youDied.setColor(sf::Color::White);
    youDied.setPosition(130, 190);
    
    returnToTitle.setFont(blackcastle);
    returnToTitle.setString("Press Enter to return to the main menu");
    returnToTitle.setCharacterSize(48);
    returnToTitle.setColor(sf::Color::White);
    returnToTitle.setPosition(325, 470);
}

void Game::titleUpdate()
{
	
}

void Game::gameUpdate()
{
	deltaTime = clock.restart();
    
    if (!theHero->IsAlive())
    {
        GameState = gameOver;
		return;
    }

	levels.update();

	float time = deltaTime.asSeconds();

	for (size_t i = 0; i < entityRegistry.size(); i++)
	{
		Entity * e = entityRegistry[i];
		e->update(time);
		e->setCollisionState(1);
		e->setGround(0);

		for (size_t i = 0; i < levels.platforms.size(); i++)
		{
			collision(e, levels.platforms[i]);
		}
	}
	//Exclude hero
	for (size_t i = 1; i < entityRegistry.size(); i++)
		hitCollision(theHero, entityRegistry[i]);

	//weapon collision against enemy(ies)
	if (theHero->attack())
		for (size_t i = 1; i < entityRegistry.size(); i++)
			hitCollision(entityRegistry[i], theHero);
	// Camera
	camera.setSize(sf::Vector2f(1280, 720));
	// If player is within the boundaries of the screen
	if (theHero->getX() > 710 && theHero->getX() < 1900)
	{
		// Set x and y position
		camera.setCenter(theHero->getX(), theHero->getY() - 100);	
	}
	// If the player is near the edge
	else
	{
		// Set only y position
		camera.setCenter(camera.getCenter().x, theHero->getY() - 100);
	}
	camera.zoom(.5);
	window.setView(camera);
	if (float(theHero->getHP()) / HERO_BASE_HP > 0)
		HPbar.setSize(sf::Vector2f(150 * (float(theHero->getHP()) / HERO_BASE_HP), 6));
	else
		HPbar.setSize(sf::Vector2f(0, 6));

	HPbar.setPosition(camera.getCenter().x-300, camera.getCenter().y-150);
}


void Game::victoryUpdate()
{
	window.setView(window.getDefaultView());
}

void Game::pauseUpdate()
{
	window.setView(window.getDefaultView());
}

void Game::gameOverUpdate()
{
	window.setView(window.getDefaultView());
}

void Game::render()
{
	// Clear the window
	window.clear();

	// Render objects
	if (GameState == titleScreen)
	{
		window.draw(title);
		window.draw(pressEnter);
	}
	else if (GameState == inGame)
	{
		camera.setViewport(sf::FloatRect(0, 0, 1, 1));
		minimap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
		minimap.setCenter(1180, 1020);
		levels.render(window);
		window.setView(minimap);
		levels.renderPlats(window);
		window.setView(camera);

		//@ Iterate through the vector, delete a "dead" entity and erase it from the vector;
		//@ Skip the first entity Hero
		int countEnemies(0);
		for (auto &entity = entityRegistry.begin() + 1; entity != entityRegistry.end();) {
			if (dynamic_cast<Enemies*>(*entity)) // check if it is an enemy
				++countEnemies;

			if (!(*entity)->IsAlive())
			{
				delete *entity;
				entity = entityRegistry.erase(entity);
			}
			else {
				++entity;
			}
		}


		if (countEnemies == 0)
			GameState = victory;


		for (size_t i = 0; i < entityRegistry.size(); i++)
		{
			
			window.setView(minimap);
			entityRegistry[i]->render(window);
			
			window.setView(camera);
			entityRegistry[i]->render(window);
		}
		
		window.draw(HPbar);
	}
	else if (GameState == pause)
	{
		window.draw(pauseText);
		window.draw(pressResume);
	}
    else if (GameState == gameOver)
    {
        window.draw(youDied);
        window.draw(returnToTitle);
    }
	else if (GameState == victory)
	{
		window.draw(victoryText);
	}

	// Display window
	window.display();
}

void Game::SaveStatsToFile()
{
	std::fstream out("../data/stats.bin", std::ios::binary | std::fstream::out);

	if (out.fail()) {
		// TODO(Dmitry): Log error
		return;
	}

	out << "Hero\n"
		<< theHero->getLevel() << std::endl
		<< theHero->getExperience() << std::endl
		<< theHero->getHP() << std::endl;

	out.close();
	// TODO(Dmitry): Log successful saving
}

void Game::LoadStats()
{
	std::ifstream inFile("../data/stats.bin", std::ios::binary);

	if (inFile.fail()) {
		// TODO(Dmitry): Log error
		return;
	}

	std::string dummy;
	float floatValue;
	int intValue;
	std::getline(inFile, dummy); // dummy call

	inFile >> intValue;
	theHero->setLevel(intValue);

	inFile >> intValue;
	theHero->setExperience(intValue);

	inFile >> floatValue;
	theHero->setHP(floatValue);

	inFile.close();

}

Hero * Game::theHero;

Hero * Game::getHero(){
	return theHero;
}

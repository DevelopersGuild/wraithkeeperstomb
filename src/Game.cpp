#include "Game.h"
#include "Enemy1.h"
#include "Constants.h"

Game::Game()
{
	// Create game render window
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chamber's Labyrinth");
	window.setMouseCursorVisible(true);

	// Limit framerate to 60 and enable Vsync
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	loadAssets();

	GameState = titleScreen;

	CreateEntities();

}

void Game::CreateEntities()
{
	theHero = new Hero;

	entityRegistry.push_back(theHero);

	enemy = new Enemy1;

	entityRegistry.push_back(enemy);
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
			collision(theHero, levels.platform.getCollisionRect());
			hitCollision(theHero, enemy);
		}
		else if (GameState == pause)
			pauseUpdate();
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
		if (event.key.code == sf::Keyboard::Escape)
			window.close();

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

				entityRegistry.clear();

				CreateEntities();

                // Move to inGame (resume playing)
				GameState = titleScreen;
				camera.setCenter(500, 500);
				//camera.setCenter(theHero->getX(), theHero->getY());
			}
		}
	}
}


void Game::collision(Hero *hero, sf::FloatRect wallBounds){
	//Affected area
	sf::FloatRect area;
	hero->setCollisionNum(1);
	if (hero->getCollisionRect().intersects(wallBounds, area))
	{
		// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
		if (area.width > area.height)
		{
			if (area.contains({ area.left, wallBounds.top }))
				//if (hero->getY()>area.top)
			{
				hero->setPosition(hero->getX(), hero->getY() - area.height);

				// Up side crash 
				//hero->setPosition( hero->getX(), hero->getY() + area.height );
				hero->setCollisionNum(0);
			}
			else
			{

				hero->setPosition(hero->getX(), hero->getY() + area.height);
				// Down side crash
				//hero->setPosition( hero->getX(), hero->getY() - area.height );
				//hero->setCollisionShit(0);

			}
			//hero->setCollisionShit(false);
		}
		else if (area.width < area.height)
		{
			//if (area.contains(hero->getX() + (hero->getCollisionRect()).width, wallBounds.top-100.f))
			if (hero->getX()<wallBounds.left)
			{
				//Right side crash
				//GameState = titleScreen;
				hero->setPosition(hero->getX() - area.width, hero->getY());
				//hero->setCollisionShit(0);
			}
			else
			{
				//Left side crash

				hero->setPosition(hero->getX() + area.width, hero->getY());
				//hero->setCollisionShit(0);
			}
		}
	}
}

void Game::hitCollision(Entity *hero, Entity *enemy)
{
	if (hero->getCollisionRect().intersects(enemy->getCollisionRect()))
		hero->onHit(enemy->getDamage());
}

void Game::loadAssets()
{
	century.loadFromFile("../assets/fonts/century.ttf");
	blackcastle.loadFromFile("../assets/fonts/blackcastle.ttf");

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
    
    if (!theHero->getAlive())
    {
        GameState = gameOver;
		return;
    }

	levels.update();

	float time = deltaTime.asSeconds();

	for (int i = 0; i < entityRegistry.size(); i++)
	{
		entityRegistry[i]->update(time);
	}

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
		levels.render(window);
		for (int i = 0; i < entityRegistry.size(); i++)
		{
			entityRegistry[i]->render(window);
		}
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

	// Display window
	window.display();
}

Hero * Game::theHero;

Hero * Game::getHero(){
	return theHero;
}

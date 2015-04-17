#include <fstream>
#include <iostream>
#include "Game.h"
#include "Constants.h"
#include "Enemy.h"
#include "EnemyMage.h"

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
	gameState_ = GameState::titleScreen;
	menuSwitch_ = MenuSwitch::continueGame;
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
	sf::Event event;
	// Main loop
	while (window.isOpen())
	{
		// Event loop
		while (window.pollEvent(event))
			handleEvent(event);
		switch (gameState_)
		{
		case GameState::titleScreen: titleUpdate(); break;
		case GameState::inGame: gameUpdate(); break;
		case GameState::pause: pauseUpdate(); break;
		case GameState::victory: victoryUpdate(); break;
		case GameState::gameOver: gameOverUpdate(); break;
		default: break;
		}
		render();
	}
}

void Game::handleEvent(sf::Event &event)
{
	if (event.type == sf::Event::Closed)
		window.close();

	// Binds escape to close the window
	if (sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape) {
			SaveStatsToFile();
			window.close();
		}

	// gameState_ handling
	if (gameState_ == GameState::titleScreen)
	{
		
	}

	if (gameState_ == GameState::inGame)
	{
		// Keys being pressed during gameplay
		if (sf::Event::KeyPressed)
		{
			// Specifically if P is pressed
			if (event.key.code == sf::Keyboard::P)
			{
				// Move to pause
				gameState_ = GameState::pause;
			}
		}
	}

	if (gameState_ == GameState::pause)
	{
		// Keys being pressed during pause screen
		if (sf::Event::KeyPressed)
		{
			// Specifically if R is pressed
			if (event.key.code == sf::Keyboard::R)
			{
				// Move to inGame (resume playing)
				gameState_ = GameState::inGame;
			}
		}
	}

	if (gameState_ == GameState::gameOver || gameState_ == GameState::victory)
	{
		// Keys being pressed during dead screen
		if (sf::Event::KeyPressed)
		{
			// Specifically if Enter is pressed
			if (event.key.code == sf::Keyboard::Return)
			{
				for (auto &it2 = projectiles.begin(); it2 != projectiles.end();)
				{
					delete *it2;
					it2 = projectiles.erase(it2);
				}
				for (auto &it : entityRegistry) {
					delete it;
				}
				CreateEntities();
                // Move to inGame (resume playing)
				gameState_ = GameState::inGame;
				camera.setCenter(500, 500);
				//camera.setCenter(theHero->getX(), theHero->getY());
			}
		}
	}

	switch (menuSwitch_)
	{
	case MenuSwitch::continueGame: 
		// Keys being pressed in menu
		if (event.type == sf::Event::KeyPressed)
		{
			// Specifically if down is pressed
			if (event.key.code == sf::Keyboard::Down)
			{
				// Move to newGame
				menuSwitch_ = MenuSwitch::newGame;
			}
			// Specifically if up is pressed
			else if (event.key.code == sf::Keyboard::Up)
			{
				// Move to exitGame
				menuSwitch_ = MenuSwitch::exitGame;
			}
		}
		break;
	case MenuSwitch::newGame: 
		// Keys being pressed in menu
		if (event.type == sf::Event::KeyPressed)
		{
			// Specifically if down is pressed
			if (event.key.code == sf::Keyboard::Down)
			{
				menuSwitch_ = MenuSwitch::loadGame;
			}
			// Specifically if up is pressed
			else if (event.key.code == sf::Keyboard::Up)
			{
				menuSwitch_ = MenuSwitch::continueGame;
			}
			if (event.key.code == sf::Keyboard::Return)
			{
				// Move to inGame (start playing)
				gameState_ = GameState::inGame;
			}
		}
		break;
	case MenuSwitch::loadGame: 
		// Keys being pressed in menu
		if (event.type == sf::Event::KeyPressed)
		{
			// Specifically if down is pressed
			if (event.key.code == sf::Keyboard::Down)
			{
				menuSwitch_ = MenuSwitch::options;
			}
			// Specifically if up is pressed
			else if (event.key.code == sf::Keyboard::Up)
			{
				menuSwitch_ = MenuSwitch::newGame;
			}
		}
		break;
	case MenuSwitch::options: 
		// Keys being pressed in menu
		if (event.type == sf::Event::KeyPressed)
		{
			// Specifically if down is pressed
			if (event.key.code == sf::Keyboard::Down)
			{
				menuSwitch_ = MenuSwitch::exitGame;
			}
			// Specifically if up is pressed
			else if (event.key.code == sf::Keyboard::Up)
			{
				menuSwitch_ = MenuSwitch::loadGame;
			}
		}
		break;
	case MenuSwitch::exitGame:
		// Keys being pressed in menu
		if (event.type == sf::Event::KeyPressed)
		{
			// Specifically if down is pressed
			if (event.key.code == sf::Keyboard::Down)
			{
				menuSwitch_ = MenuSwitch::continueGame;
			}
			// Specifically if up is pressed
			else if (event.key.code == sf::Keyboard::Up)
			{
				menuSwitch_ = MenuSwitch::options;
			}
			else if (event.key.code == sf::Keyboard::Return)
			{
				window.close();
			}
		}
		break;
	default:
		break;
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
	if ((dynamic_cast<Enemy*>(hitter) || dynamic_cast<Hero*>(hitter)) && getsHit->getCollisionRect().intersects(hitter->getDamagingRect()))
	{
		getsHit->onHit(hitter->getDamage());
		if (knockBackTime.getElapsedTime().asMilliseconds() > 300)
		{
			getsHit->knockBack(hitter->getX(), hitter->getY());
			
			knockBackTime.restart(); //warning: knockbackTime is shared between hero and enemy
		}
		hitter->freeze();
	}

}

bool Game::projectileCollide(Entity *getsHit, Projectile *proj)
{
	if ((dynamic_cast<Enemy*>(getsHit) || dynamic_cast<Hero*>(getsHit)) && getsHit->getCollisionRect().intersects(proj->getAttackRect()))
	{
		getsHit->onHit(proj->getDamage());
		if (knockBackTime.getElapsedTime().asMilliseconds() > 300)
		{
			getsHit->knockBack(proj->getX(), proj->getY());

			knockBackTime.restart(); //warning: knockbackTime is shared between hero and enemy
		}
		return true;
	}
	else
		return false;
}

void Game::loadAssets()
{
	gothicbold.loadFromFile("../assets/fonts/gothicb.ttf");
	blackcastle.loadFromFile("../assets/fonts/blackcastle.ttf");

	HPbar.setSize(sf::Vector2f(150, 6));
	HPbar.setOutlineColor(sf::Color::White);
	HPbar.setFillColor(sf::Color::Green);
	HPbar.setOutlineThickness(1.5);
	HPbar.setOrigin(0, 6);
	HPbar.setPosition(camera.getCenter().x - 300, camera.getCenter().y- 580);

	MPbar.setSize(sf::Vector2f(150, 6));
	MPbar.setOutlineColor(sf::Color::White);
	MPbar.setFillColor(sf::Color::Blue);
	MPbar.setOutlineThickness(1.5);
	MPbar.setOrigin(0, 6);
	MPbar.setPosition(camera.getCenter().x - 300, camera.getCenter().y - 570);

	title.setFont(blackcastle);
	title.setString("Chamber's Labyrinth");
	title.setCharacterSize(150);
	title.setColor(sf::Color::White);
	title.setPosition(75, 25);

	continueButton.setFont(gothicbold);
	continueButton.setString("CONTINUE");
	continueButton.setCharacterSize(48);
	continueButton.setColor(sf::Color::White);
	continueButton.setPosition(510, 310);

	continueButtonDisabled.setFont(gothicbold);
	continueButtonDisabled.setString("CONTINUE");
	continueButtonDisabled.setCharacterSize(48);
	continueButtonDisabled.setColor(sf::Color::Color(100, 100, 100, 255));
	continueButtonDisabled.setPosition(510, 310);

	newGameButton.setFont(gothicbold);
	newGameButton.setString("NEW GAME");
	newGameButton.setCharacterSize(48);
	newGameButton.setColor(sf::Color::White);
	newGameButton.setPosition(510, 360);

	loadGameButton.setFont(gothicbold);
	loadGameButton.setString("LOAD GAME");
	loadGameButton.setCharacterSize(48);
	loadGameButton.setColor(sf::Color::White);
	loadGameButton.setPosition(510, 410);

	optionsButton.setFont(gothicbold);
	optionsButton.setString("OPTIONS");
	optionsButton.setCharacterSize(48);
	optionsButton.setColor(sf::Color::White);
	optionsButton.setPosition(510, 460);

	exitGameButton.setFont(gothicbold);
	exitGameButton.setString("EXIT GAME");
	exitGameButton.setCharacterSize(48);
	exitGameButton.setColor(sf::Color::White);
	exitGameButton.setPosition(510, 510);

	continueButtonHL.setFont(gothicbold);
	continueButtonHL.setString("CONTINUE");
	continueButtonHL.setCharacterSize(48);
	continueButtonHL.setColor(sf::Color::Yellow);
	continueButtonHL.setStyle(sf::Text::StrikeThrough);
	continueButtonHL.setPosition(510, 310);

	continueButtonHLDisabled.setFont(gothicbold);
	continueButtonHLDisabled.setString("CONTINUE");
	continueButtonHLDisabled.setCharacterSize(48);
	continueButtonHLDisabled.setColor(sf::Color::Color(100, 100, 100, 255));
	continueButtonHLDisabled.setStyle(sf::Text::StrikeThrough);
	continueButtonHLDisabled.setPosition(510, 310);

	newGameButtonHL.setFont(gothicbold);
	newGameButtonHL.setString("NEW GAME");
	newGameButtonHL.setCharacterSize(48);
	newGameButtonHL.setColor(sf::Color::Yellow);
	newGameButtonHL.setStyle(sf::Text::StrikeThrough);
	newGameButtonHL.setPosition(510, 360);

	loadGameButtonHL.setFont(gothicbold);
	loadGameButtonHL.setString("LOAD GAME");
	loadGameButtonHL.setCharacterSize(48);
	loadGameButtonHL.setColor(sf::Color::Yellow);
	loadGameButtonHL.setStyle(sf::Text::StrikeThrough);
	loadGameButtonHL.setPosition(510, 410);

	optionsButtonHL.setFont(gothicbold);
	optionsButtonHL.setString("OPTIONS");
	optionsButtonHL.setCharacterSize(48);
	optionsButtonHL.setColor(sf::Color::Yellow);
	optionsButtonHL.setStyle(sf::Text::StrikeThrough);
	optionsButtonHL.setPosition(510, 460);

	exitGameButtonHL.setFont(gothicbold);
	exitGameButtonHL.setString("EXIT GAME");
	exitGameButtonHL.setCharacterSize(48);
	exitGameButtonHL.setColor(sf::Color::Yellow);
	exitGameButtonHL.setStyle(sf::Text::StrikeThrough);
	exitGameButtonHL.setPosition(510, 510);

	victoryText.setFont(gothicbold);
	victoryText.setString("Victory!");
	victoryText.setCharacterSize(100);
	victoryText.setColor(sf::Color::White);
	victoryText.setPosition(480, 225);

	pauseText.setFont(gothicbold);
	pauseText.setString("Game Paused");
	pauseText.setCharacterSize(100);
	pauseText.setColor(sf::Color::White);
	pauseText.setPosition(280, 225);

	pressResume.setFont(gothicbold);
	pressResume.setString("Press R to Resume");
	pressResume.setCharacterSize(48);
	pressResume.setColor(sf::Color::White);
	pressResume.setPosition(420, 425);
    
    youDied.setFont(gothicbold);
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
		gameState_ = GameState::gameOver;
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

	//@ Iterate through the vector, delete a "dead" entity and erase it from the vector;
	//@ Skip the first entity Hero
	int countEnemies(0);
	for (auto &entity = entityRegistry.begin() + 1; entity != entityRegistry.end();) {

		if (dynamic_cast<Enemy*>(*entity)) // check if it is an enemy
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
		gameState_ = GameState::victory;

	//projectile collision check
	for (auto &iter = projectiles.begin(); iter != projectiles.end();)
	{//check who shot the projectile
		if ((*iter)->is_shot_by_hero())
		{//check collision for every enemy
			for (unsigned int i = 1; i < entityRegistry.size() && iter != projectiles.end(); i++)
			{
				if (projectileCollide(entityRegistry[i], *iter))
				{
					delete *iter;
					iter = projectiles.erase(iter);
				}
			}
			if (iter != projectiles.end())
				++iter;
		}
		else //shot by an enemy
		{
			if (projectileCollide(theHero, *iter))
			{
				delete *iter;
				iter = projectiles.erase(iter);
			}
			else
				++iter;
		}
	}

	//check if the hero is shooting projectile
	//TODO move to Hero?
	if (theHero->projectileShoot())
	{
		Projectile* proj = new HolyOrb(theHero->getX(), theHero->getY(), true, theHero->getFaceRight());

		if (theHero->getMP() >= proj->getManaCost())
		{
			theHero->consumeMP(proj->getManaCost());
			projectiles.push_back(proj);
			theHero->setProjectileCooldown(proj->getCooldownDuration());
		}
		else
			delete proj;
		//other projectiles
	}

	//TODO move to EnemyMage
	for (auto &entity = entityRegistry.begin(); entity != entityRegistry.end();)
	{
		if (dynamic_cast<EnemyMage*>(*entity))
			if ((static_cast<EnemyMage*>(*entity))->projectileShoot())
			{
				Projectile* proj = new FireBall((*entity)->getX(), (*entity)->getY(), false, (static_cast<EnemyMage*>(*entity))->getFaceRight());

				projectiles.push_back(proj);
				static_cast<EnemyMage*>(*entity)->setProjectileCooldown(proj->getCooldownDuration());
				//other projectiles
			}
		entity++;
	}

	//iterate through all shot projectiles
	for (auto &iter = projectiles.begin(); iter != projectiles.end();)
	{
		if ((*iter)->overRange())
		{ //when max projectile range is reached
			delete *iter;
			iter = projectiles.erase(iter); // returns the next iterator
		}
		else
		{
			(*iter)->update();
			++iter;
		}
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
	//HP
	if (theHero->getHP() / HERO_BASE_HP > 0)
		HPbar.setSize(sf::Vector2f(150 * (theHero->getHP() / HERO_BASE_HP), 6));
	else
		HPbar.setSize(sf::Vector2f(0, 6));

	HPbar.setPosition(camera.getCenter().x-300, camera.getCenter().y-150);

	//MP
	if (theHero->getMP() / HERO_BASE_MP > 0)
		MPbar.setSize(sf::Vector2f(150 * (theHero->getMP() / HERO_BASE_MP), 6));
	else
		MPbar.setSize(sf::Vector2f(0, 6));

	MPbar.setPosition(camera.getCenter().x - 300, camera.getCenter().y - 140);
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
	if (gameState_ == GameState::titleScreen)
	{
		window.draw(title);
		// if (current session save file found)
		//		window.draw(continueButton);
		// else
				window.draw(continueButtonDisabled);
		window.draw(newGameButton);
		window.draw(loadGameButton);
		window.draw(optionsButton);
		window.draw(exitGameButton);
		switch (menuSwitch_)
		{
		case MenuSwitch::continueGame:
			// if (current session save file found)
			//		window.draw(continueButtonHL);
			// else
					window.draw(continueButtonHLDisabled); 
			break;
		case MenuSwitch::newGame: window.draw(newGameButtonHL); break;
		case MenuSwitch::loadGame: window.draw(loadGameButtonHL); break;
		case MenuSwitch::options: window.draw(optionsButtonHL); break;
		case MenuSwitch::exitGame: window.draw(exitGameButtonHL); break;

		default:
			break;
		}

	}
	else if (gameState_ == GameState::inGame)
	{
		camera.setViewport(sf::FloatRect(0, 0, 1, 1));
		minimap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
		minimap.setCenter(1180, 1020);
		levels.render(window);
		window.setView(minimap);
		levels.renderPlats(window);
		window.setView(camera);

		for (size_t i = 0; i < entityRegistry.size(); i++)
		{
			
			window.setView(minimap);
			entityRegistry[i]->render(window);
			
			window.setView(camera);
			entityRegistry[i]->render(window);
		}

		for (auto &iter = projectiles.begin(); iter != projectiles.end();)
		{ 
			(*iter)->render(window);
			++iter;
		}
		
		window.draw(HPbar);
		window.draw(MPbar);
	}
	else if (gameState_ == GameState::pause)
	{
		window.draw(pauseText);
		window.draw(pressResume);
	}
	else if (gameState_ == GameState::gameOver)
    {
        window.draw(youDied);
        window.draw(returnToTitle);
    }
	else if (gameState_ == GameState::victory)
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

Game::~Game()
{
	for (auto &proj : projectiles)
	{
		delete proj;
	}
	projectiles.clear();
}

#include "Game.h"
#include "Constants.h"
#include "Enemy.h"
#include "EnemyMage.h"
#include "FirstBoss.h"
#include "Paths.h"

std::vector<Entity *> Game::entityRegistry;

Game::Game()
{
	// Create game render window
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Wraithkeeper's Tomb");
	window.setMouseCursorVisible(true);
	window.setKeyRepeatEnabled(false);
	
	// Set the Icon
	sf::Image icon;
	//if (!icon.loadFromFile(resourcePath() + "assets/sprites/reaper.png")) {
	//	return EXIT_FAILURE;
	//}
	//window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	// Limit framerate to 60 and enable Vsync
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	loadAssets();
	gameState_ = GameState::titleScreen;
	menuSwitch_ = MenuSwitch::play;
	CreateEntities();
	LoadStats();
	minimap.setSize(1280, 720);
	minimap.setCenter(1280, 720);
	camera.setCenter(710, theHero->getY() - 100);
	knockBackTime.restart();
	dmgTextRegistry.clear();
	dmgSpriteRegistry.clear();
	doorOpen = false;
	bossFirstEncounter = true;
	current_level = 1;
}

void Game::CreateEntities()
{
	entityRegistry.clear();
	theHero = new Hero;
	entityRegistry.push_back(theHero);
	levels.roomGenerater();
}

void Game::mainLoop()
{
	sf::Event event;
	// Start dTime out as zero. It will increase until it is time to move 1 frame forward
	dTime = sf::Time::Zero;
	// Main loop
	while (window.isOpen())
	{
		sf::Time elapsedTime = gClock.restart(); // Time elapsed according to system time not per cylcle through the loop
		dTime += elapsedTime; // Add system time to dTime.

		// If dTime becomes greater than 1/60 of a second, the game updates
		while (dTime > TimePerFrame) {
			// Reset deltaTime
			dTime -= TimePerFrame;
			// Event loop
			while (window.pollEvent(event))
				handleEvent(event);
			/*std::cout << theHero->getY() << '\n';*/
			switch (gameState_)
			{
			case GameState::titleScreen: titleUpdate(); break;
			case GameState::inGame: gameUpdate(); break;
			case GameState::pause: pauseUpdate(); break;
			case GameState::enterDoor: enterDoorUpdate(); break;
			case GameState::victory: victoryUpdate(); break;
			case GameState::gameOver: gameOverUpdate(); break;
			case GameState::dialogueState: textUpdate(); break;
			default: break;
			}
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
			// Input for Hero actions
			theHero->handleEvent(event);
			// Specifically if P is pressed
			if (event.key.code == sf::Keyboard::P)
			{
				// Move to pause
				gameState_ = GameState::pause;
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				//enable hero to enter door when up is pressed
				if (doorOpen)
					enterDoor(theHero);
			}

		}
	}
	if (gameState_ == GameState::titleScreen)
	{
		switch (menuSwitch_)
		{
		case MenuSwitch::play:
			// Keys being pressed in menu
			if (event.type == sf::Event::KeyPressed)
			{
				// Specifically if down is pressed
				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up)
					menuSwitch_ = MenuSwitch::exit;
				else if (event.key.code == sf::Keyboard::Return)
					gameState_ = GameState::inGame;
			}
			break;
		case MenuSwitch::exit:
			// Keys being pressed in menu
			if (event.type == sf::Event::KeyPressed)
			{
				// Specifically if down is pressed
				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up)
					menuSwitch_ = MenuSwitch::play;
				else if (event.key.code == sf::Keyboard::Return)
					window.close();
			}
			break;
		default:
			break;
		}
	}

	if (gameState_ == GameState::dialogueState)
	{
		// Keys being pressed during gameplay
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Space))
		{
			dialogueRegistry.pop();
			if (dialogueRegistry.empty())
				gameState_ = GameState::inGame;
		}
	}
	/*if (gameState_ == GameState::enterDoor)
	{
		// options to save or quit?
	}*/
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
				for (auto it2 = projectiles.begin(); it2 != projectiles.end();)
				{
					delete *it2;
					it2 = projectiles.erase(it2);
				}
				for (auto &it : entityRegistry) {
					delete it;
				}
				levels.cleanup();
				CreateEntities();
                // Move to inGame (resume playing)
				gameState_ = GameState::inGame;
				camera.setCenter(500, 500);
				//camera.setCenter(theHero->getX(), theHero->getY());
			}
		}
	}
}


void Game::collision(Entity *hero, Platform& plat){
	//Affected area
	sf::FloatRect wallBounds = plat.getCollisionRect();
	sf::FloatRect area;
	/*std::cout << hero->getX() << " " << hero->getY() << '\n';*/
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
		float dmgDealt = getsHit->onHit(hitter->getDamage());
		getsHit->backDirection(hitter->getX(), hitter->getY());
		hitter->freeze();
		dmgTextAppears(dynamic_cast<Enemy*>(getsHit), getsHit->getX(), getsHit->getY(), static_cast<int>(dmgDealt));
	}
}

bool Game::projectileCollide(Entity *getsHit, Projectile *proj)
{
	if ((dynamic_cast<Enemy*>(getsHit) || dynamic_cast<Hero*>(getsHit)) && getsHit->getCollisionRect().intersects(proj->getAttackRect()))
	{
		float dmgDealt = getsHit->onHit(proj->getDamage());
		getsHit->backDirection(proj->getX(), proj->getY());
		dmgTextAppears(dynamic_cast<Enemy*>(getsHit), getsHit->getX(), getsHit->getY(), static_cast<int>(dmgDealt));
		return true;
	}
	else
		return false;
}

void Game::enterDoor(Entity *hero)
{
	if (hero->getCollisionRect().intersects(levels.getDoor().getDoorRect()))
	{
		doorOpen = false;
		bossFirstEncounter = true;
		levels.incrBossFightChance();
		levels.bossAppearance();
		cleanupAll();
		levels.cleanup();
		gameState_ = GameState::enterDoor;
	}
}

void Game::loadTextLineHL(sf::Text &text, std::string line, int yPos)
{
	text.setFont(gothicbold);
	text.setString(line);
	text.setCharacterSize(48);
	text.setColor(sf::Color::Yellow);
	text.setPosition(30.f, float(yPos));
}

void Game::loadTextLine(sf::Text &text, std::string line, int yPos)
{
	text.setFont(gothicbold);
	text.setString(line);
	text.setCharacterSize(48);
	text.setColor(sf::Color::White);
	text.setPosition(30.f, float(yPos));
}

void Game::loadDialogueBoxAndFont(sf::Text &text)
{
	textBox.setFillColor(sf::Color(0, 0, 0, 125));
	textBox.setPosition(camera.getCenter().x - 500, camera.getCenter().y + 75);
	textBox.setSize(sf::Vector2f(1000.f, 200.f));

	text.setFont(blackcastle);
	text.setCharacterSize(24);
	text.setColor(sf::Color::White);
	text.setPosition(camera.getCenter().x - 300, camera.getCenter().y + 100);
}

void Game::loadAssets()
{
	gothicbold.loadFromFile(resourcePath() + "assets/fonts/gothicb.ttf");
	blackcastle.loadFromFile(resourcePath() + "assets/fonts/blackcastle.ttf");
	lato.loadFromFile(resourcePath() + "assets/fonts/lato.ttf");

	menuTexture.loadFromFile(resourcePath() + "assets/sprites/dungeonmenu.png");
	menuSprite.setTexture(menuTexture);
	menuSprite.scale(2.f, 1.5f);

	soulTexture.loadFromFile(resourcePath() + "assets/sprites/redsoul.png");
	soulSprite.setTexture(soulTexture);
	soulSprite.setTextureRect(sf::IntRect(0, 0, 76, 115));

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

	title.setFont(lato);
	title.setString("WRAITHKEEPER'S TOMB");
	title.setCharacterSize(56);
	title.setColor(sf::Color::White);
	title.setPosition(600, 620);

	//Menu buttons
	loadTextLine(playButton, "PLAY", 30);
	playButton.setFont(lato);
	loadTextLine(exitButton, "EXIT", 80);
	exitButton.setFont(lato);

	//Highlighted
	loadTextLineHL(playButtonHL, "PLAY", 30);
	playButtonHL.setFont(lato);
	loadTextLineHL(exitButtonHL, "EXIT", 80);
	exitButtonHL.setFont(lato);

	loadTextLine(victoryText, "Victory!", 225);
	victoryText.setPosition(550, 225);

	loadTextLine(pauseText, "Game Paused", 225);
	pauseText.setPosition(280, 225);

	loadTextLine(pressResume, "Press R to resume", 425);
	pressResume.setPosition(420, 425);
    
	loadTextLine(youDied, "YOU DIED", 425);
	youDied.setFont(gothicbold);
	youDied.setCharacterSize((200));
    youDied.setPosition(130, 190);
    
    returnToTitle.setFont(blackcastle);
    returnToTitle.setString("Press Enter to return to the main menu");
    returnToTitle.setCharacterSize(48);
    returnToTitle.setColor(sf::Color::White);
    returnToTitle.setPosition(325, 470);

	loading.setFont(blackcastle);
	loading.setString("Loading...");
	loading.setCharacterSize(64);
	loading.setColor(sf::Color::Red);
	loading.setPosition(1000, 610);

	//damage text
	dmgText.setFont(lato);
	dmgText.setCharacterSize(19);
}

void Game::dmgTextAppears(bool isEnemy, float x_pos, float y_pos, int dmg)
{
	if (dmg == 0)
		return;

	dmgText.setPosition(x_pos, y_pos-128);
	dmgText.setString(std::to_string(dmg));

	if (isEnemy) //the one who gets hit
	{
		if (theHero->getCritStatus())
			dmgText.setColor(sf::Color::Yellow);
		else
			dmgText.setColor(sf::Color::White);
	}
	else
		dmgText.setColor(sf::Color::Red);

	dmgTextRegistry.push_back(dmgText);
	//dmgSpriteRegistry.push_back(soulSprite);
}

void Game::titleUpdate()
{
	
}

//Also checks for victory
int Game::cleanupEntities()
{
	//@ Iterate through the vector, delete a "dead" entity and erase it from the vector;
	//@ Skip the first entity Hero
	int countEnemies(0);
	for (auto entity = entityRegistry.begin() + 1; entity != entityRegistry.end();) {

		if (dynamic_cast<Enemy*>(*entity)) // check if it is an enemy
			++countEnemies;

		if (!(*entity)->IsAlive())
		{
			if (!dynamic_cast<Hero*>(*entity) && !dynamic_cast<Enemy*>(*entity))
			{
				dmgTextRegistry.push_back((*entity)->getEffectText());
			}
			delete *entity;
			entity = entityRegistry.erase(entity);
		}
		else {
			++entity;
		}
	}

	if (countEnemies == 0)
	{
		if (levels.getIsBoss())
		{
			levels.levelup();
		}
		doorOpen = levels.setDoor(1);
	}
		

	return countEnemies;
}

void Game::cleanupProjectiles()
{
	//iterate through all shot projectiles
	for (auto iter = projectiles.begin(); iter != projectiles.end();)
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
}

void Game::cleanupAll()
{//delete all entities and projectiles (except hero), empty containers
	for (auto &proj : projectiles)
		delete proj;

	for (auto entity = entityRegistry.begin() + 1; entity != entityRegistry.end();)
	{
		delete *entity;
		entity = entityRegistry.erase(entity);
	}

	projectiles.clear();
	entityRegistry.clear();
	dmgTextRegistry.clear();
}

void Game::gameUpdate()
{
	deltaTime = clock.restart();

	float time = deltaTime.asSeconds();

	if (!theHero->IsAlive())
	{
		gameState_ = GameState::gameOver;
		return;
	}

	levels.update();
	current_level = levels.getLevel();
	if (current_level == 4)
		gameState_ = GameState::victory;

	//Dialogue appears upon boss first encounter in boss stage
	if (levels.getIsBoss() && bossFirstEncounter)
	{
		for (size_t i = 0; i < entityRegistry.size(); i++)
			if (dynamic_cast<FirstBoss*>(entityRegistry[i])) //check if it's the first encounter
				if (dialogueRegistry.empty() && !static_cast<FirstBoss*>(entityRegistry[i])->getFirstEncounter())
				{//upon the first encounter
					bossFirstEncounter = false;
					gameState_ = GameState::dialogueState;
					insertDialogue(current_level); //dialogue based on level
				}
	}

	//Loading time when changing stage
	if (stageLoadingTime != 1.0)
		stageLoadingTime = 1.0;

	//Platform collision and souls
	for (size_t i = 0; i < entityRegistry.size(); i++)
	{
		Entity * e = entityRegistry[i];
		e->update(time);
		e->setCollisionState(1);
		e->setGround(0);

		if (!(e->IsAlive()) && e->IsCreature())
		{
			soulRelease = true;
			soulCount = 120;
			soulSprite.setPosition(e->getX() - 50, e->getY() -150);
		}
		if (soulRelease)
			soulAnim();

		for (size_t i = 0; i < levels.platforms.size(); i++)
		{
			collision(e, levels.platforms[i]);
		}
	}

	//Exclude hero
	for (size_t i = 1; i < entityRegistry.size(); i++)
		hitCollision(theHero, entityRegistry[i]);

	//weapon collision against enemy(ies)
	if (theHero->getAttacking())
		for (size_t i = 1; i < entityRegistry.size(); i++)
			hitCollision(entityRegistry[i], theHero);

	cleanupEntities();

	//projectile collision check
	for (auto iter = projectiles.begin(); iter != projectiles.end();)
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
	//TODO move to Hero using scheduler task
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

	//TODO move to EnemyMage using scheduler task
	for (auto entity = entityRegistry.begin(); entity != entityRegistry.end();)
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

	cleanupProjectiles(); 

	//Check if dmg texts expire
	for (auto txt = dmgTextRegistry.begin(); txt != dmgTextRegistry.end();)
	{
		if ((*txt).getColor().a <= 10)
			txt = dmgTextRegistry.erase(txt);
		else
		{
			int r = (*txt).getColor().r;
			int g = (*txt).getColor().g;
			int b = (*txt).getColor().b;
			int a = (*txt).getColor().a;
			(*txt).setColor(sf::Color(r, g, b, a - 3));
			txt++;
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

	camera.zoom(.6f);
	window.setView(camera);
	//HP
	if (theHero->getHP() / HERO_BASE_HP > 0)
		HPbar.setSize(sf::Vector2f(150 * (theHero->getHP() / HERO_BASE_HP), 6));
	else
		HPbar.setSize(sf::Vector2f(0, 6));

	HPbar.setPosition(camera.getCenter().x-380, camera.getCenter().y-190);

	//MP
	if (theHero->getMP() / HERO_BASE_MP > 0)
		MPbar.setSize(sf::Vector2f(150 * (theHero->getMP() / HERO_BASE_MP), 6));
	else
		MPbar.setSize(sf::Vector2f(0, 6));

	MPbar.setPosition(camera.getCenter().x - 380, camera.getCenter().y - 200);
}

void Game::soulAnim() {
	if (soulCount > 113)
		soulFrame = 0;
	else if (soulCount > 106)
		soulFrame = 1;
	else if (soulCount > 96)
		soulFrame = 2;
	else
		soulFrame = 3;
	soulSprite.setTextureRect(sf::IntRect(soulFrame * 76, 0, 76, 159));
	soulSprite.move(0, soulFrame * -.35f);
	soulSprite.setColor(sf::Color(255, 100, 100, sf::Uint8(70 + soulCount * 1.5)));
	soulCount--;
	if (soulCount == 0)
		soulRelease = false;
}

void Game::enterDoorUpdate()
{
	deltaTime = clock.restart();
	window.setView(window.getDefaultView());
	stageLoadingTime -= deltaTime.asSeconds();

	if (stageLoadingTime <= 0)
	{
		entityRegistry.push_back(theHero);
		levels.roomGenerater();
		gameState_ = GameState::inGame;
	}
}

void Game::textUpdate()
{
	deltaTime = clock.restart();
	levels.update();
	theHero->setAction(0);
	float time = deltaTime.asSeconds();

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

	camera.zoom(.6f);
	window.setView(camera);
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
		window.draw(menuSprite);
		window.draw(title);
		window.draw(playButton);
		window.draw(exitButton);
		switch (menuSwitch_)
		{
		case MenuSwitch::play: window.draw(playButtonHL); break;
		case MenuSwitch::exit: window.draw(exitButtonHL); break;

		default:
			break;
		}

	}
	else if (gameState_ == GameState::inGame)
	{
		camera.setViewport(sf::FloatRect(0, 0, 1, 1));
		minimap.setViewport(sf::FloatRect(0.f, 0.f, 0.f, 0.f));
		minimap.setCenter(1180, 1020);
		levels.render(window);
		window.setView(minimap);
		levels.renderPlats(window);
		window.setView(camera);

		for (size_t i = 0; i < entityRegistry.size(); i++)
		{
			window.setView(camera);
			entityRegistry[i]->render(window);
		}

		for (auto iter = projectiles.begin(); iter != projectiles.end();)
		{ 
			(*iter)->render(window);
			++iter;
		}
		
		for (size_t i = 0; i < dmgTextRegistry.size(); i++)
		{
			dmgTextRegistry[i].setFont(lato);
			window.draw(dmgTextRegistry[i]);
		}

		if (soulCount > 0)
			window.draw(soulSprite);

		window.draw(HPbar);
		window.draw(MPbar);
	}
	else if (gameState_ == GameState::dialogueState)
	{
		camera.setViewport(sf::FloatRect(0, 0, 1, 1));
		levels.render(window);
		window.setView(camera);

		for (size_t i = 0; i < entityRegistry.size(); i++)
		{
			window.setView(camera);
			entityRegistry[i]->render(window);
		}
		if (!dialogueRegistry.empty())
		{
			window.draw(textBox);
			window.draw(dialogueRegistry.front());
		}
	}
	/*else if (gameState_ == GameState::enterDoor)
	{
			tips/hints?
			options to save/quit?
	}*/
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
	else if (gameState_ == GameState::enterDoor)
	{
		soulCount = 0;
		window.draw(loading);
	}
	// Display window
	window.display();
}

void Game::insertDialogue(int scriptNum)
{
	loadDialogueBoxAndFont(dialogue);

	switch (scriptNum)
	{
	case 1: //Encounter with the first boss
		dialogue.setString("???: \"You... You are one of us. Why are you trying to escape?\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("Player: \"I look nothing like you, demon!\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("???: \"How pitiful... You have not realized it yet, have you?\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("???: \"But it does not matter. You will not go any further than this.\"");
		dialogueRegistry.push(dialogue);
		break;
	case 2: //Encounter with the second boss
		dialogue.setString("???: \"Why are you desperately trying to escape?\nDo you not realize what awaits you?\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("Player: \"There... is someone I must save.\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("Player: \"Get out of my way, demon!\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("???: \"Ah, I see... how pitiful.\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("???: \"But this is as far as you go. Turn back or face eternal torment!\"");
		dialogueRegistry.push(dialogue);
		break;
	case 3: //Encounter with the final boss
		dialogue.setString("Player \"Why are you trying to halt my advance, demon?\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("???: \"There is nothing beyond this point. Only suffering awaits you.\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("Player: \"Then I will face it! I must save my son!\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("???: \"You still do not get it, do you?\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("Player: \"I... am dead, aren't I?\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("???: \"Yes, little wraith. You are one of us now\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("Wraithkeeper: \"I am the Wraithkeeper. I shall give you power you seek\"");
		dialogueRegistry.push(dialogue);
		dialogue.setString("Wraithkeeper: \"...but only if you worthy enough to obtain it!\"");
		dialogueRegistry.push(dialogue);
		break;
	default:
		break;
	}
}

void Game::SaveStatsToFile()
{
	std::fstream out(savePath() + "stats.bin", std::ios::binary | std::fstream::out);

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
	std::ifstream inFile(savePath() + "stats.bin", std::ios::binary);

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
	for (auto &ent : entityRegistry)
	{
		delete ent;
	}
	
	projectiles.clear();
	entityRegistry.clear();
	dmgTextRegistry.clear();
	while (!dialogueRegistry.empty())
		dialogueRegistry.pop();
}

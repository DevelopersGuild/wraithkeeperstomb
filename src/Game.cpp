#include "Game.h"

using namespace std;

Game::Game()
{
	// Create game render window
	window.create(sf::VideoMode(1280, 720), "Chamber's Labyrinth");
	window.setMouseCursorVisible(true);

	// Limit framerate to 60 and enable Vsync
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	loadAssets();

	GameState = titleScreen;
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
		else if (GameState == inGame)
			gameUpdate();
		else if (GameState == pause)
			pauseUpdate();
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
}


void Game::collision(sf::RectangleShape hero, sf::RectangleShape wall){
sf::FloatRect area;
		if(hero.getGlobalBounds().intersects(wall.getGlobalBounds(),area))
		{
			// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
			if (area.width > area.height)
			{
				if (area.contains( area.left, hero.getPosition().y ))
				{
				// Up side crash
				hero.setPosition( hero.getPosition().x, hero.getPosition().y - area.height );
				
				}
				
				else
				{
				// Down side crash
				hero.setPosition( hero.getPosition().x, hero.getPosition().y + area.height );
				}
				
			}
			else if (area.width < area.height)
			{
				if (area.contains( hero.getPosition().x + hero.getGlobalBounds().width - 1.f, area.top + 1.f ))
				{
					//Right side crash
					//shape.setOrigin(shape.getOrigin().x - area.width, shape.getOrigin().y);
					hero.setPosition( hero.getPosition().x - area.width, hero.getPosition().y );
				}
				else
				{
					//Left side crash
					hero.setPosition(hero.getPosition().x + area.width, hero.getPosition().y );
				}
			}
			
		}
}

void Game::loadAssets()
{
	century.loadFromFile("../assets/fonts/century.ttf");

	title.setFont(century);
	title.setString("Chamber's Labyrinth");
	title.setCharacterSize(100);
	title.setColor(sf::Color::White);
	title.setPosition(150, 225);

	pressEnter.setFont(century);
	pressEnter.setString("Press Enter to Begin");
	pressEnter.setCharacterSize(48);
	pressEnter.setColor(sf::Color::White);
	pressEnter.setPosition(420, 425);
}

void Game::titleUpdate()
{
	
}

void Game::gameUpdate()
{
	levels.update();
	hero.update();
}

void Game::pauseUpdate()
{
	
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
		hero.render(window);
	}
	else if (GameState == pause)
	{
		// Load pause stuff
	}

	// Display window
	window.display();
}

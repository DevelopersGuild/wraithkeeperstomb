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
}

void Game::mainLoop()
{
	// Main loop
	while (window.isOpen())
	{
		// Event loop
		while (window.pollEvent(event))
			handleEvent(event);
		update();
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
}

void Game::update()
{
	levels.update();
	hero.update();
}

void Game::render()
{
	// Clear the window
	window.clear();

	// Render objects
	levels.render(window);
	hero.render(window);

	// Display window
	window.display();
}

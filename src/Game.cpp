#include "Game.h"

Game::Game()
{
	window.create(sf::VideoMode(1280, 720), "Chamber's Labyrinth");
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
}

void Game::mainLoop()
{
	while (window.isOpen())
	{
		while (window.pollEvent(event))
			handleEvent(event);
	}
}

void Game::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::Closed)
		window.close();
	if (sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
			window.close();
}

void Game::render()
{
	window.clear();
	window.display();
}

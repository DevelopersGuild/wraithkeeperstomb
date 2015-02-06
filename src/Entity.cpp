#include "Entity.h"
#include "Constants.h"

Entity::Entity()
{
	// Load Entity texture, assign to sprite, set starting sprite dimensions

	// Initialize basic Entity stats
	isAlive = true;
}

void Entity::left()
{
	Sprite.move(-Speed, 0.f);
}

void Entity::right()
{
	Sprite.move(Speed, 0.f);
}

void Entity::jump()
{
	// not yet written
}

void Entity::update()
{
	// Handle movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		left();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		right();

	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		jump();

	// Check if alive
	if (HP <= 0)
		isAlive = false;
}

void Entity::render(sf::RenderWindow &window)
{
	window.draw(Sprite);
}
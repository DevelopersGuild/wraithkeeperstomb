#include "Entity.h"
#include "Constants.h"

Entity::Entity()
{
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

void Entity::render(sf::RenderWindow &window)
{
	window.draw(Sprite);
}

void Entity::onHit(int dmg)
{
	//for the armorless
}
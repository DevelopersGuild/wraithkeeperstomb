#include "Entity.h"
#include "Constants.h"

Entity::Entity()
{
	// Initialize basic Entity stats
}

void Entity::setPosition(float x, float y)
{
	Sprite.setPosition(x,y);
}

void Entity::render(sf::RenderWindow &window)
{
	window.draw(Sprite);
}

void Entity::update(float time){

}

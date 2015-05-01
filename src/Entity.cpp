#include "Entity.h"
#include "Constants.h"

Entity::Entity()
{
	// Initialize basic Entity stats
	collisionNum = 0;
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

void Entity::setCollisionState(int state)
{
	collisionNum = state;
}

void Entity::setGround(Platform * ground_){
	ground = ground_;
}

void Entity::doPhysics(float seconds)
{
	//Gravity implementation
	if (collisionNum == 0)
	{
		velocity.y += GRAVITY * seconds * 265 * (collisionNum == 0 ? 0 : 1);
	}
	Sprite.move(velocity);
}
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
	//if (collisionNum == 0)
	//{
	//	velocity.y += GRAVITY * seconds * 265 * (collisionNum == 0 ? 0 : 1);
	//}
	//Sprite.move(velocity);



	//Gravity implementation
	if (Sprite.getPosition().y + Sprite.getScale().y < GROUND_HEIGHT + 10)// || collisionNum == 0) //This should later be changed to a collision with groud boolean
	{
		velocity.y += GRAVITY * seconds * seconds * 265 * collisionNum;
		Sprite.move(0.f, velocity.y);

		if (collisionNum == 0){
			velocity.y = 0;
		}
	}
	else
	{
		velocity.y = 0;
		//if (jumpCooldown < 4)
		//jumpCooldown++;
		//Sprite.setPosition(Sprite.getPosition().x, 1840);
	}

	Sprite.move(velocity);

}

void Entity::backDirection(float hitter_x, float hitter_y)
{
	if ((getX() - hitter_x) < 0)
		backing = 'l'; //knock back to the left
	else
		backing = 'r'; //knock back to the right
}
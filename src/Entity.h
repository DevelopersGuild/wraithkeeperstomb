#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Platform.h"

class Entity
{
protected:
	sf::Texture Texture;
	sf::Sprite Sprite;
	bool is_alive_;
	char backing;

	sf::Vector2f velocity;

	Platform * ground = 0;

	int collisionNum;

public:
	Entity();
	virtual ~Entity() { }
	virtual void render(sf::RenderWindow& window);
	virtual void update(float time);
	virtual void freeze() = 0;
	virtual void knockBack(float) = 0;

	void backDirection(float, float);

	void doPhysics(float seconds);

	void setCollisionState(int state);

	void setGround(Platform*);

	virtual void onHit(float dmg)
	{ return; }

	virtual void setPosition(float, float);

	const float getX()
	{ return Sprite.getPosition().x; }

	const float getY()
	{ return Sprite.getPosition().y; }

	virtual const float getDamage()
	{ return 0; }
	
	// Real function - Testing the other right now
	//const sf::FloatRect getCollisionRect()
	//{ return Sprite.getGlobalBounds(); }
	
	virtual const sf::FloatRect getCollisionRect()
	{ return Sprite.getGlobalBounds(); }

	virtual const sf::FloatRect getDamagingRect()
	{ return Sprite.getGlobalBounds(); }

	virtual bool IsAlive() const
	{ return is_alive_; }

};

#endif

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <string>

class Entity
{
protected:
	sf::Texture Texture;
	sf::Sprite Sprite;
	bool is_alive_;
	bool is_creature_ = false;
	char backing;

	sf::Vector2f velocity;

	Platform * ground = 0;

	int collisionNum;

	sf::Font lato;
	sf::Text effectText;
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

	void setTextFont(sf::Font font)
	{ effectText.setFont(font); }

	virtual float onHit(float dmg)
	{ return 0; }

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

	sf::Text getEffectText()
	{ return effectText; }

	virtual bool IsAlive() const
	{ return is_alive_; }

	virtual bool IsCreature() const
	{ return is_creature_; }
};

#endif

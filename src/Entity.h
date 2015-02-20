#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::Texture Texture;
	sf::Sprite Sprite;
public:
	Entity();
	virtual ~Entity() { }
	virtual void render(sf::RenderWindow& window);
	virtual void update(float time);
	virtual void onHit(float dmg)
	{ return; }

	void setPosition(float, float);

	const float getX()
	{
		return Sprite.getPosition().x;
	}
	const float getY()
	{
		return Sprite.getPosition().y;
	}
	virtual const float getDamage()
	{
		return 0;
	}
	const sf::FloatRect getCollisionRect()
	{
		return Sprite.getGlobalBounds();
	}
};

#endif

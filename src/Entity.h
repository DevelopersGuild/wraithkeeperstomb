#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::Texture Texture;
	sf::Sprite Sprite;

	int HP;
	bool isAlive;
	float Speed;
	float SpeedMultiplier;
	int armor;

	void jump();
	void left();
	void right();
public:
	Entity();
	virtual ~Entity() { }
	virtual void render(sf::RenderWindow& window);
	virtual void update(float time);
	virtual void onHit(int dmg) = 0;

	void setPosition(float, float);

	const float getX()
	{
		return Sprite.getPosition().x;
	}
	const float getY()
	{
		return Sprite.getPosition().y;
	}

	const sf::FloatRect getCollisionRect()
	{
		return Sprite.getGlobalBounds();
	}
	const bool getAlive()
	{
		return isAlive;
	}
	const int getHP()
	{
		return HP;
	}
	virtual int getDamage()
	{
		return 0;
	}
};

#endif

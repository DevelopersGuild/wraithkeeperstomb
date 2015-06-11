#ifndef WEAPONS_H
#define WEAPONS_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

class Hero;
class Entity;

class Weapons
{
protected:
	sf::Vector2i anim;
	int frameTimer;
	int xFrame;
	int yFrame;
	bool isCrit;
	float base_damage;
	float damage;
	float range;
	float crit_chance;
	float crit_multiplier;
	float damage_fluctuation;
	sf::Texture Texture;
	sf::Sprite Sprite;
	sf::Clock cooldown;
public:
	Weapons();
	virtual ~Weapons();
	virtual void render(sf::RenderWindow& window);
	virtual void update(bool);
	float dmgRandomizer(float fluctuation);
	float critical(float multiplier);
	void setPosition(float, float);
	virtual bool attack();
	//Accessors
	const float getX()
	{ return Sprite.getPosition().x; }
	const float getY()
	{ return Sprite.getPosition().y; }
	const float getDamage() { return damage; }
	const float getCritStatus() { return isCrit; }
	virtual const sf::FloatRect getAttackRect(bool);
	const sf::Clock getCooldown() { return cooldown; }
};


#endif

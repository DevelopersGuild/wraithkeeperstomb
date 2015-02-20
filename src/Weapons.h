#ifndef WEAPONS_H
#define WEAPONS_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Weapons : public Entity
{
protected:
	sf::Texture WeaponTexture;
	sf::Sprite WeaponSprite;

	float damage;
	float range;
	float crit_chance;
	float crit_multiplier;
	float damage_fluctuation;
public:
	Weapons();
	virtual ~Weapons();
	virtual void render(sf::RenderWindow& window);
	virtual void update(float time);
	float dmgRandomizer(float fluctuation);
	float critical(float multiplier);
	//Accessors
	const float getDamage() { return damage; }
};


#endif
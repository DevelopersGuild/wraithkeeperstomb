#ifndef WEAPONS_H
#define WEAPONS_H

#include <SFML/Graphics.hpp>

class Weapons
{
protected:
	sf::Texture WeaponTexture;
	sf::Sprite WeaponSprite;

	int damage;
	int range;
	float cooldown;
	float crit_chance;
	float crit_multiplier;
	int damage_fluctuation;
public:
	Weapons();
	virtual ~Weapons();
	virtual void render(sf::RenderWindow& window);
	virtual void update(float time);
	int dmgRandomizer(int fluctuation);
	float critical(float multiplier);
	//Accessors
	int getDamage() { return damage; }
	float getCooldown() { return cooldown; }
};


#endif
#ifndef ENEMIES_H
#define ENEMIES_H
#include "Hero.h"
#include "Entity.h"

class Enemies: public Entity
{
protected:
	int damage;
public:
	Enemies();
	void update();
	void render(sf::RenderWindow& window);
	bool heroDetection(Hero* hero);
	void onHeroDetected(Hero* hero);
	int getDamage() { return damage; }
};

#endif

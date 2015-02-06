#ifndef ENEMY2_H
#define ENEMY2_H
#include "Enemies.h"

class Enemy2 : public Enemies
{
private:

public:
	Enemy2();
	void update();
	void render(sf::RenderWindow& window);
	bool heroDetection(Hero* hero);
};

#endif
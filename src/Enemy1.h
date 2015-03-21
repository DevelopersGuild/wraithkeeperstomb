#ifndef ENEMY1_H
#define ENEMY1_H

#include "Enemies.h"

// Mage Baddie
class Enemy1 : public Enemies
{
private:

public:
	Enemy1();

	void update(float time);

	void jump();
	//void onHeroDetected(Hero* hero); // if it responds differently
};

#endif

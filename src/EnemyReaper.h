#ifndef ENEMY1_H
#define ENEMY1_H

#include "Enemy.h"

// Mage Baddie
class EnemyReaper : public Enemy
{
private:

public:
	EnemyReaper();

	void update(float time);
	void onHeroDetected(Hero* hero);
	void jump();
	//void onHeroDetected(Hero* hero); // if it responds differently
};

#endif

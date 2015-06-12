#ifndef ENEMY1_H
#define ENEMY1_H

#include "Enemy.h"

// Mage Baddie
class EnemyReaper : public Enemy
{
private:

public:
	EnemyReaper();

	void animate();
	void update(float time);
	void onHeroDetected(Hero* hero);
	void jump();
	const sf::FloatRect getCollisionRect();
	//void onHeroDetected(Hero* hero); // if it responds differently
};

#endif

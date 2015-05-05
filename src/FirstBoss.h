#ifndef FIRSTBOSS_H
#define FIRSTBOSS_H
#include "Enemy.h"

// First Boss
class FirstBoss : public Enemy
{
private:

public:
	FirstBoss();
	void update(float time);
	void onHeroDetected(Hero* hero);
	void jump();
	//void onHeroDetected(Hero* hero); // if it responds differently
};

#endif

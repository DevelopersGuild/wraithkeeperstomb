#ifndef ENEMY2_H
#define ENEMY2_H
#include "Enemy.h"

//mage baddie
class EnemyMage : public Enemy
{
private:
	float projectileCooldown;
public:
	EnemyMage();
	void update(float time);
	bool projectileShoot();
	void jump();
	void setProjectileCooldown(float cd) { projectileCooldown = cd; }
	float getProjectileCooldown() { return projectileCooldown; }
	//void onHeroDetected(Hero* hero); // if it responds differently
};

#endif

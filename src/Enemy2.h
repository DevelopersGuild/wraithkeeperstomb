#ifndef ENEMY2_H
#define ENEMY2_H
#include "Enemies.h"

//mage baddie
class Enemy2 : public Enemies
{
private:
	float projectileCooldown;
public:
	Enemy2();
	void update(float time);
	bool projectileShoot();
	void jump();
	void setProjectileCooldown(float cd) { projectileCooldown = cd; }
	float getProjectileCooldown() { return projectileCooldown; }
	//void onHeroDetected(Hero* hero); // if it responds differently
};

#endif
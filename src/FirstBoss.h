#ifndef FIRSTBOSS_H
#define FIRSTBOSS_H
#include "Enemy.h"

// First Boss
class FirstBoss : public Enemy
{
private:
	bool first_encounter; //read dialogue upon first encounter
public:
	FirstBoss();
	void update(float time);
	bool heroDetection(Hero* hero);
	void onHeroDetected(Hero* hero);
	const sf::FloatRect getCollisionRect();
	const sf::FloatRect getDamagingRect();
	bool getFirstEncounter() { return first_encounter; }
	void jump();
	//void onHeroDetected(Hero* hero); // if it responds differently
};

#endif

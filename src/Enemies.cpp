#include "Enemies.h"
#include "Constants.h"

Enemies::Enemies()
{

}

void Enemies::update(Hero* hero)
{
	// Detection
	if (heroDetection(hero))
		onHeroDetected(hero);
	// Check if alive
	if (HP <= 0)
		isAlive = false;
}

bool Enemies::heroDetection(Hero* hero)
{
	if ((getX() - hero->getX()) <= ENEMY_DETECTION_RADIUS && (hero->getX() - getX()) <= ENEMY_DETECTION_RADIUS)
		return true;
	else return false;
}

void Enemies::onHeroDetected(Hero* hero)
{
	if ((getX() - hero->getX()) > 0)
		left();
	else
		right();
}
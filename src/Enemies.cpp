#include "Enemies.h"
#include "Constants.h"
#include "Game.h"


Enemies::Enemies()
{

}

void Enemies::chaseHero()
{
	// Detection
	if (heroDetection(Game::getHero()))
		onHeroDetected(Game::getHero());
	// Check if alive
	if (HP <= 0)
		isAlive = false;
}

bool Enemies::heroDetection(Hero* hero)
{
	if ((getX() - hero->getX()) <= ENEMY_DETECTION_RADIUS && (hero->getX() - getX()) <= ENEMY_DETECTION_RADIUS)
		return true;
	else 
		return false;
}

void Enemies::onHeroDetected(Hero* hero)
{
	if ((getX() - hero->getX()) > 0)
		left();
	else
		right();
}

void Enemies::onHit(int dmg)
{
	if (dmg > armor)
		HP = HP - (dmg - armor / 4);
	else
		HP = HP - rand() % 10;
}
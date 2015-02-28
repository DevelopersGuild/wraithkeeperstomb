#include "Enemy1.h"
#include "Constants.h"
#include <ctime>

Enemy1::Enemy1()
{
	// Load Enemies texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile("../assets/sprites/magebaddie.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128);
	Sprite.setPosition(1280, 1360);

	// Initialize basic Enemies stats
	HP = ENEMY1_BASE_HP;
	speedMultiplier = 1;
	speed = ENEMY1_BASE_SPEED * speedMultiplier;
	damage = ENEMY1_DAMAGE;
	isAlive = true;
	armor = ENEMY1_ARMOR;

	srand((unsigned int)time(NULL));
}

void Enemy1::update(float time)
{
	chaseHero();
}

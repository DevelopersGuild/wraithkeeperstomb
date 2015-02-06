#include "Enemies.h"
#include "Enemy1.h"
#include "Constants.h"

Enemy1::Enemy1()
{
	// Load Enemies texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile("../assets/sprites/Enemies.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128);
	Sprite.setPosition(640, 640);

	// Initialize basic Enemies stats
	HP = ENEMY1_BASE_HP;
	SpeedMultiplier = 1;
	Speed = ENEMY1_BASE_SPEED * SpeedMultiplier;
	damage = ENEMY1_DAMAGE;
}

bool Enemy1::heroDetection(Hero* hero)
{
	if ((getX() - hero->getX()) <= ENEMY_DETECTION_RADIUS && (hero->getX() - getX()) <= ENEMY_DETECTION_RADIUS)
		return true;
}
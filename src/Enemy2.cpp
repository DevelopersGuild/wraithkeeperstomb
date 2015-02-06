#include "Enemies.h"
#include "Enemy2.h"
#include "Constants.h"

Enemy2::Enemy2()
{
	// Load Enemies texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile("../assets/sprites/Enemies.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128);
	Sprite.setPosition(640, 640);

	// Initialize basic Enemies stats
	HP = ENEMY2_BASE_HP;
	SpeedMultiplier = 1;
	Speed = ENEMY2_BASE_SPEED * SpeedMultiplier;
	damage = ENEMY2_DAMAGE;
}

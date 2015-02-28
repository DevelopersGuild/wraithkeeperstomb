#include "Enemies.h"
#include "Enemy2.h"
#include "Constants.h"
#include <ctime>

Enemy2::Enemy2()
{
	// Load Enemies texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile("../assets/sprites/enemy2.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128); // waiting for spritesheet
	Sprite.setPosition(640, 640); // edit

	// Initialize basic Enemies stats
	HP = ENEMY2_BASE_HP;
	speedMultiplier = 1;
	speed = ENEMY2_BASE_SPEED * speedMultiplier;
	damage = ENEMY2_DAMAGE;
	is_alive_ = true;
	armor = ENEMY2_ARMOR;

	srand((unsigned int)time(NULL));
}

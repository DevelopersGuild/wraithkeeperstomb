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

	Freeze.restart().asSeconds();

	// Initialize basic Enemies stats
	HP = ENEMY1_BASE_HP;
	speedMultiplier = 1;
	speed = ENEMY1_BASE_SPEED * speedMultiplier;
	damage = ENEMY1_DAMAGE;
	is_alive_ = true;
	armor = ENEMY1_ARMOR;
	isChase = true;

	srand((unsigned int)time(NULL));
}

void Enemy1::update(float time)
{
	if (Freeze.getElapsedTime().asSeconds() > 1)
	{
		Freeze.restart().asSeconds();
		isChase = true;
	}
	velocity.x = velocity.x / 2;
	if (isChase)
	{
		chaseHero();
	}
	doPhysics(time);
		
}

void Enemy1::jump()
{
	velocity.y -= HERO_JUMP_VELOCITY;

	if (velocity.y < 0){
		Sprite.move(velocity);
		velocity.y += GRAVITY;
	}
}

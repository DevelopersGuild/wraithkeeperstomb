#include "Enemy2.h"
#include "Constants.h"
#include <ctime>

Enemy2::Enemy2()
{
	// Load Enemies texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile("../assets/sprites/magebaddie.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128);
	Sprite.setPosition(1280, 1360);

	// Initialize basic Enemies stats
	HP = ENEMY2_BASE_HP;
	speedMultiplier = 1;
	speed = ENEMY2_BASE_SPEED * speedMultiplier;
	damage = ENEMY2_DAMAGE;
	isShooter = true;
	armor = ENEMY2_ARMOR;
	faceRight = true;
	projectileCooldown = 0.0;
	patrol_origin = getX();
	Enemies();

	srand((unsigned int)time(NULL));
}

void Enemy2::update(float time)
{
	if (Freeze.getElapsedTime().asSeconds() < 1)
		isChase = false;
	else if (heroDetected)
		isChase = true;
	velocity.x = velocity.x / 2;

	chaseHero(); //check hero detection

	doPhysics(time);

	if (projectileCooldown > 0)
		projectileCooldown -= time;
	
	if(!heroDetected)
		areaPatrol(time);
}

bool Enemy2::projectileShoot()
{
	//magic cast animation
	if (projectileCooldown <= 0 && heroDetected)
		return true;
	else
		return false;
}

void Enemy2::jump()
{
	velocity.y -= HERO_JUMP_VELOCITY;

	if (velocity.y < 0){
		Sprite.move(velocity);
		velocity.y += GRAVITY;
	}
}

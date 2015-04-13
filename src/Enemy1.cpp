#include "Enemy1.h"
#include "Constants.h"
#include <ctime>

Enemy1::Enemy1()
{
	// Load Enemies texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile("../assets/sprites/reaper.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(64, 128);
	Sprite.setPosition(1000, 1360);

	// Initialize basic Enemies stats
	HP = ENEMY1_BASE_HP;
	speedMultiplier = 1;
	speed = ENEMY1_BASE_SPEED * speedMultiplier;
	damage = ENEMY1_DAMAGE;
	isShooter = false;
	armor = ENEMY1_ARMOR;
	faceRight = true;
	Enemies();

	srand((unsigned int)time(NULL));
}

void Enemy1::update(float time)
{
	if (Freeze.getElapsedTime().asSeconds() < 1)
		isFrozen = true;
	else
		isFrozen = false;
	velocity.x = velocity.x / 2;

	chaseHero(); //check hero detection

	if (!heroDetected)
	{
		areaPatrol(time);
		if (speedMultiplier != 1)
			speedMultiplier = 1; //unalerted speed
	}
	else
	{
		if (speedMultiplier == 1)
			speedMultiplier = 2; //chasing speed
		doPhysics(time);
	}
	if (isFrozen)
		velocity.x = 0.f;
	else
		speed = ENEMY1_BASE_SPEED * speedMultiplier;

	if (faceRight)
		Sprite.setScale(-1.f, 1.f); //until animation is available
	else
		Sprite.setScale(1.f, 1.f);
}

void Enemy1::jump()
{
	velocity.y -= HERO_JUMP_VELOCITY;

	if (velocity.y < 0){
		Sprite.move(velocity);
		velocity.y += GRAVITY;
	}
}

void Enemy1::onHeroDetected(Hero* hero)
{
	if (getY() < hero->getY())
		jump();
	else if ((getX() - hero->getX()) > 0)
	{
		left();
		faceRight = false;
	}
	else
	{
		right();
		faceRight = true;
	}
}
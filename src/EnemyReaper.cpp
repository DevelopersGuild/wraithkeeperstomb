#include "EnemyReaper.h"
#include "Constants.h"
#include "Paths.h"
#include <ctime>
#include <iostream>

EnemyReaper::EnemyReaper()
{
	// Load Enemies texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile(resourcePath() + "assets/sprites/reaper.png");
	Sprite.setTexture(Texture);
	Sprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
	Sprite.setOrigin(64, 128);
	Sprite.setPosition(1000, 1424);

	// Initialize basic Enemies stats
	HP = ENEMY1_BASE_HP;
	speedMultiplier = 1;
	speed = ENEMY1_BASE_SPEED * speedMultiplier;
	damage = ENEMY1_DAMAGE;
	isShooter = false;
	armor = ENEMY1_ARMOR;
	faceRight = true;
	Enemy();

	srand((unsigned int)time(NULL));
}

void EnemyReaper::animate() {
	if (frameTimer > 8)
		xFrame++;
	if (xFrame > 2)
		xFrame = 0;
	if (frameTimer > 8)
		frameTimer = 0;
	frameTimer++;
}

void EnemyReaper::update(float time)
{
	
	if (Freeze.getElapsedTime().asSeconds() < 2)
		isFrozen = true;
		
	else
		isFrozen = false;
	velocity.x = velocity.x / 2;

	chaseHero(); //check hero detection

	if (!heroDetected)
	{
		if (speedMultiplier != 1)
			speedMultiplier = 1; //unalerted speed
		areaPatrol(time);
	}
	else
	{
		if (speedMultiplier == 1)
			speedMultiplier = 2; //chasing speed
	}
	if (isFrozen)
		velocity.x = 0.f;
	else
		speed = ENEMY1_BASE_SPEED * speedMultiplier;

	if (faceRight)
		Sprite.setScale(-1.f, 1.f); //until animation is available
	else
		Sprite.setScale(1.f, 1.f);

	if (collisionNum == 2 || collisionNum == 0)
		velocity.y = 0;

	animate();
	Sprite.setTextureRect(sf::IntRect(xFrame * 128, yFrame * 128, 128, 128));

	knockBack(time);
	doPhysics(.1*time);
}

void EnemyReaper::jump()
{
	collisionNum = 1;
	velocity.y -= HERO_JUMP_VELOCITY;

	if (collisionNum == 2){
		velocity.y = 0;
	}

	if (velocity.y < 0){
		velocity.y += GRAVITY;
		Sprite.move(velocity);
	}
}

void EnemyReaper::onHeroDetected(Hero* hero)
{
	if (getY() < hero->getY() && collisionNum == 0)
		jump();
	if ((getX() - hero->getX()) > 20)
	{
		left();
		faceRight = false;
	}
	else if ((hero->getX() - getX()) > 20)
	{
		right();
		faceRight = true;
	}
}

const sf::FloatRect EnemyReaper::getCollisionRect()
{
	sf::FloatRect bigBox = Sprite.getGlobalBounds();
	return sf::FloatRect(bigBox.left + 10.f, bigBox.top + 8.f, bigBox.width - 10.f, bigBox.height - 8.f);
}
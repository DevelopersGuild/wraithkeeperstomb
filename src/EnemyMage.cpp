#include "EnemyMage.h"
#include "Constants.h"
#include "Paths.h"
#include <ctime>

EnemyMage::EnemyMage()
{
	// Load Enemies texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile(resourcePath() + "assets/sprites/magebaddie.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128);
	Sprite.setPosition(1280, 1424);

	// Initialize basic Enemies stats
	HP = ENEMY2_BASE_HP;
	speedMultiplier = 1;
	speed = ENEMY2_BASE_SPEED * speedMultiplier;
	damage = ENEMY2_DAMAGE;
	isShooter = true;
	armor = ENEMY2_ARMOR;
	faceRight = true;
	projectileCooldown = 0.0;
	Enemy();


	srand((unsigned int)time(NULL));
}

void EnemyMage::update(float time)
{
	if (Freeze.getElapsedTime().asSeconds() < 1)
		isFrozen = true;
	else
		isFrozen = false;
	velocity.x = velocity.x / 2;

	chaseHero(); //check hero detection

	if (projectileCooldown > 0)
		projectileCooldown -= time;
	
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
		Sprite.setScale(-1.f, 1.f); //until animation
	else
		Sprite.setScale(1.f, 1.f);

	doPhysics(time);
}

bool EnemyMage::projectileShoot()
{
	//magic cast animation
	if (projectileCooldown <= 0 && heroDetected)
		return true;
	else
		return false;
}

void EnemyMage::jump()
{
	velocity.y -= HERO_JUMP_VELOCITY;

	if (velocity.y < 0){
		Sprite.move(velocity);
		velocity.y += GRAVITY;
	}
}

const sf::FloatRect EnemyMage::getCollisionRect()
{
	sf::FloatRect bigBox = Sprite.getGlobalBounds();
	return sf::FloatRect(bigBox.left + 10.f, bigBox.top + 8.f, bigBox.width - 10.f, bigBox.height - 8.f);
}

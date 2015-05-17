#include "FirstBoss.h"
#include "Constants.h"
#include "Paths.h"
#include <ctime>

FirstBoss::FirstBoss() {
	// Load Enemies texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile(resourcePath() + "assets/sprites/tempBoss2.png");
	Sprite.setTexture(Texture);
	//Sprite.setOrigin(50, 45);
	Sprite.setPosition(1000, 1360);

	// Initialize basic Enemies stats
	HP = BOSS_BASE_HP;
	speedMultiplier = 0.36;
	speed = BOSS_BASE_SPEED * speedMultiplier;
	damage = BOSS_DAMAGE;
	isShooter = false;
	armor = BOSS_ARMOR;
	faceRight = true;
	Enemy();

	srand((unsigned int)time(NULL));
}

void FirstBoss::update(float time)
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
	}
	if (isFrozen)
		velocity.x = 0.f;
	else
		speed = ENEMY1_BASE_SPEED * speedMultiplier;

	if (faceRight)
		Sprite.setScale(-1.f, 1.f); //until animation is available
	else
		Sprite.setScale(1.f, 1.f);
	doPhysics(.2*time);
}

void FirstBoss::jump()
{
	velocity.y -= HERO_JUMP_VELOCITY;

	if (velocity.y < 0){
		Sprite.move(velocity);
		velocity.y += GRAVITY;
	}
}

void FirstBoss::onHeroDetected(Hero* hero)
{
	/*if (getY() < hero->getY())
		jump();
	else */if ((getX() - hero->getX()) > 10)
	{
		left();
		faceRight = false;
	}
	else if ((hero->getX() - getX()) > 10)
	{
		right();
		faceRight = true;
	}
}

const sf::FloatRect FirstBoss::getCollisionRect()
{
	sf::FloatRect bigBox = Sprite.getGlobalBounds();
	return sf::FloatRect(bigBox.left + 10.f, bigBox.top, bigBox.width - 10.f, bigBox.height);
}

const sf::FloatRect FirstBoss::getDamagingRect()
{// shrink the bounding box
	float left = Sprite.getGlobalBounds().left + 10;
	float top = Sprite.getGlobalBounds().top + 10;
	float width = Sprite.getGlobalBounds().width - 20;
	float height = Sprite.getGlobalBounds().height - 20;
	sf::FloatRect collisionRect(left, top, width, height);
	return collisionRect;
}
#include "Enemy.h"
#include "Constants.h"
#include "Game.h"
#include <iostream>

Enemy::Enemy()
{
	Freeze.restart().asSeconds();
	is_alive_ = true;
	heroDetected = false;
	patrol_right = true;
	isFrozen = false;
	patrol_pause = 0.0; //? sec pause
	if (faceRight)
		Sprite.setScale(-1.f, 1.f);
}

void Enemy::chaseHero()
{
	// Detection
	if (heroDetection(Game::getHero()))
		onHeroDetected(Game::getHero());
	// Check if alive
	if (HP <= 0)
		is_alive_ = false;
}

void Enemy::left()
{
	faceRight = false;
	velocity.x = (velocity.x + 3* -speed) / 4;
}

void Enemy::right()
{
	faceRight = true;
	velocity.x = (velocity.x + 3*speed) / 4;
}

bool Enemy::heroDetection(Hero* hero)
{
	if ((getX() - hero->getX()) <= ENEMY_DETECTION_RADIUS) // && (hero->getX() - getX()) <= ENEMY_DETECTION_RADIUS && (getY() - hero->getY()) <= ENEMY_DETECTION_RADIUS)
	{
		heroDetected = true;
		return true;
	}
	else
	{
		heroDetected = false;
		return false;
	}
}

void Enemy::onHeroDetected(Hero* hero)
{
	 if ((getX() - hero->getX()) > 0)
	{
		faceRight = false;
	}
	else
	{
		faceRight = true;
	}
}

void Enemy::onHit(float dmg)
{
	std::cout << "attacked";
	if (dmg > armor)
		HP = HP - (dmg - armor / 4);
	else
		HP = HP - rand() % 10;
}

void Enemy::freeze()
{
	Freeze.restart().asSeconds();
	if (!isFrozen)
		isFrozen = true;
}

void Enemy::knockBack(float hitter_x, float hitter_y)
{
	if ((getX() - hitter_x) <= 1)
	{
		Sprite.move((15 * -speed), 0.f);
	}
	else
	{
		Sprite.move((15 * speed), 0.f);
	}
}

void Enemy::areaPatrol(float deltaTime)
{
	if (speedMultiplier != 1)
		speedMultiplier = 1;
	if (patrol_pause > 0)
	{
		if (getX() >= patrol_origin + PATROL_RADIUS)
			if (patrol_right)//on the right edge of patrol boundary
				patrol_right = false;

		else if (getX() <= patrol_origin - PATROL_RADIUS)
			if (!patrol_right)//on the left edge of patrol boundary
				patrol_right = true;

		patrol_pause -= deltaTime;
		doPhysics(deltaTime);
	}
	else if (getX() <= patrol_origin + PATROL_RADIUS && getX() >= patrol_origin - PATROL_RADIUS)
	{//within patrol boundary
		if (patrol_right)
			right();
		else
			left();
		doPhysics(deltaTime);

		//check if out of boundary after the movement
		if (getX() >= patrol_origin + PATROL_RADIUS || getX() <= patrol_origin - PATROL_RADIUS)
			patrol_pause = 3.0; //few sec pause
	}
	else //not frozen, but somehow still outside patrol boundary
	{
		if (getX() >= patrol_origin + PATROL_RADIUS)
		{
			if (patrol_right)
				patrol_right = false;
			left();
		}
		else
		{
			if (!patrol_right)
				patrol_right = true;
			right();
		}
		doPhysics(deltaTime);
	}
}
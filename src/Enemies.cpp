#include "Enemies.h"
#include "Constants.h"
#include "Game.h"
#include <iostream>

Enemies::Enemies()
{
	Freeze.restart().asSeconds();
	isChase = false;
	is_alive_ = true;
	heroDetected = false;
	patrol_right = true;
	patrol_pause = 0.0; //? sec pause
}

void Enemies::chaseHero()
{
	// Detection
	if (heroDetection(Game::getHero()))
		onHeroDetected(Game::getHero());
	// Check if alive
	if (HP <= 0)
		is_alive_ = false;
}

void Enemies::left()
{
	faceRight = false;
	velocity.x = (velocity.x + 3* -speed) / 4;
}

void Enemies::right()
{
	faceRight = true;
	velocity.x = (velocity.y + 3*speed) / 4;
}

bool Enemies::heroDetection(Hero* hero)
{
	if ((getX() - hero->getX()) <= ENEMY_DETECTION_RADIUS && (hero->getX() - getX()) <= ENEMY_DETECTION_RADIUS && (getY() - hero->getY()) <= ENEMY_DETECTION_RADIUS)
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

void Enemies::onHeroDetected(Hero* hero)
{
	if (getY() < hero->getY())
		jump();
	else if ((getX() - hero->getX()) > 0)
	{
		faceRight = false;
	}
	else
	{
		faceRight = true;
	}
}

void Enemies::onHit(float dmg)
{
	std::cout << "attacked";
	if (dmg > armor)
		HP = HP - (dmg - armor / 4);
	else
		HP = HP - rand() % 10;
}

void Enemies::freeze()
{
	Freeze.restart().asSeconds();
	if (isChase)
		isChase = false;
}

void Enemies::knockBack(float hitter_x, float hitter_y)
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

void Enemies::areaPatrol(float deltaTime)
{
	if (patrol_pause > 0)
	{
		if (getX() >= patrol_origin + PATROL_RADIUS)
		{//on the right edge of patrol boundary
			if (patrol_right)
				patrol_right = false;
			patrol_pause -= deltaTime;
			if (patrol_pause <= 0) //move back into the boundary
				while (getX() >= patrol_origin + PATROL_RADIUS)
				{
					left();
					Sprite.move(velocity);
				}
		}
		else if (getX() <= patrol_origin - PATROL_RADIUS)
		{//on the left edge of patrol boundary
			if (!patrol_right)
				patrol_right = true;
			patrol_pause -= deltaTime;
			if (patrol_pause <= 0) //move back into the boundary
				while (getX() <= patrol_origin - PATROL_RADIUS)
				{
					right();
					Sprite.move(velocity);
				}
		}
	}
	else //sprite within the patrol boundary
	{
		if (patrol_right)
			right();
		else
			left();
		//check if out of boundary after the movement
		if (getX() >= patrol_origin + PATROL_RADIUS || getX() <= patrol_origin - PATROL_RADIUS)
			patrol_pause = 3.0; //few sec pause
	}
}
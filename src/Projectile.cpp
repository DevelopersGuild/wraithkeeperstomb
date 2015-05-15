#include "Projectile.h"
#include "Constants.h"

Projectile::Projectile(float shooter_x, float shooter_y, bool byHero)
{
	Sprite.setOrigin(16, 16);
	Sprite.setPosition(shooter_x, shooter_y - 62);

	shot_by_hero = byHero;
	cooldown.restart().asSeconds();

	sf::Vector2i anim(sf::Vector2i(0, 0));

	srand((unsigned int)time(NULL));
}

void Projectile::flightAnim()
{
	//if (castTime > 34)
	//	anim.y = 1;
	//else if (castTime > 13)
	//	anim.y = 2;
	//else
	//	anim.y = 1;
	//castTime--;
}

const sf::FloatRect Projectile::getCollisionRect()
{
	sf::FloatRect collisionRect(getX(), getY(), 32.f, 32.f);
	return collisionRect;
}

bool Projectile::attack()
{
	if (cooldown.getElapsedTime().asSeconds() > cooldownDuration)
	{
		castTime = 50; //for animation?
		cooldown.restart().asSeconds();
		return true;
	}
	else
		return false;
}

void Projectile::update()
{
	Sprite.move(speed, 0);
	if (speed > 0)
		range -= speed;
	else
		range += speed;

	//if (castTime > -7)
	//	flightAnim();
	//else
	//	anim.y = 0;
	//if (faceRight)
	//	Sprite.setScale(1, 1);
	//else
	//	Sprite.setScale(-1, 1);
	//Sprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 64, 64, 64));
}

bool Projectile::overRange()
{
	if (range <= 0)
		return true;
	return false;
}

const sf::FloatRect Projectile::getAttackRect()
{
	return sf::FloatRect(getX(), getY(), 10, 10);
}

Projectile::~Projectile()
{

}

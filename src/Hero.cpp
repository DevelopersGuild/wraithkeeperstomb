#include "Entity.h"
#include "Hero.h"
#include "Constants.h"
#include <ctime>

Hero::Hero()
{
	// Load hero texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile("../assets/sprites/hero.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128);
	Sprite.setPosition(80, 1360);
	sf::Vector2f velocity(sf::Vector2f(0, 0));
	sf::Vector2i anim(sf::Vector2i(0, 1));

	// Initialize basic hero stats
	level = HERO_BASE_LEVEL;
	armor = HERO_BASE_ARMOR;
	heroHP = HERO_BASE_HP;
	isAlive = true;
	heroSpeedMultiplier = 1;
	heroSpeed = HERO_BASE_SPEED * heroSpeedMultiplier;
	jumpTimer = 0; //Timer for jump function duration
	jumpCooldown = 0;
	xFrame = 0;
	yFrame = 0;
	frameTimer = 0;
	faceRight = true;

	srand(time(0));
}

void Hero::walkAnim()
{
	//Determine row in sprite sheet
	if (faceRight)
		anim.y = 1;
	else
		anim.y = 2;
	//Move frame forward
	if (frameTimer > 4)
	{
		if (xFrame != 4 && xFrame != 9)
		{
			frameTimer = 0;
			xFrame++;
		}
		else if (frameTimer > 6)
		{
			frameTimer = 0;
			xFrame++;
		}
		if (xFrame == 10)
			xFrame = 0;
	}
	anim.x = xFrame;
	frameTimer++;
}

void Hero::left()
{
	velocity.x = -heroSpeed;
	Sprite.move(velocity.x, 0.f);
	walkAnim();
}

void Hero::right()
{
	velocity.x = heroSpeed;
	Sprite.move(velocity.x, 0.f);
	walkAnim();
}

void Hero::jump(float seconds)
{
	if (jumpTimer < 22 && jumpCooldown > 3)
	{
		velocity.y = -350;
		velocity.y += GRAVITY*seconds*jumpTimer*2;
		Sprite.move(velocity*seconds);
		velocity.y = 0;
		jumpTimer++;
	}
	if (Sprite.getPosition().y + Sprite.getScale().y >= 1359)
	{
		jumpTimer = 0;
		jumpCooldown = 0;
	}
}

void Hero::update(float seconds)
{
	if (jumpTimer != 0)
		jump(seconds);
	{
		// Handle movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			faceRight = false;
			anim.x = 1;
			left();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			faceRight = true;
			anim.x = 0;
			right();
		}
		else
		{
			velocity.x = 0;
			xFrame = 0;
			if (faceRight)
			{
				anim.x = 0; 
				anim.y = 0;
			}
			else
			{
				anim.x = 1;
				anim.y = 0;
			}
		}

		// Jump
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			jump(seconds);

		// Check if alive
		if (heroHP <= 0)
			isAlive = false;

		//Gravity implementation
		if (Sprite.getPosition().y + Sprite.getScale().y < 1350) //This should later be changed to a collision with groud boolean
		{
			velocity.y += GRAVITY * seconds * seconds*50;
			Sprite.move(0.f, velocity.y);
		}
		else
		{
			velocity.y = 0;
			if (jumpCooldown < 4)
				jumpCooldown++;
			Sprite.setPosition(Sprite.getPosition().x, 1360);
		}
	}
}

void Hero::render(sf::RenderWindow &window)
{
	Sprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 128, 64, 128));
	if (isAlive)
		window.draw(Sprite);
}

void Hero::onHit(int dmg)
{
	if (dmg > armor)
		heroHP = heroHP - (dmg - armor / 4 + rand() % 3);
	else
		heroHP = heroHP - rand() % 5;
}

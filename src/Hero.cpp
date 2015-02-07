#include "Entity.h"
#include "Hero.h"
#include "Constants.h"

Hero::Hero()
{
	// Load hero texture, assign to sprite, set starting sprite dimensions
<<<<<<< HEAD
	heroTexture.loadFromFile("../assets/sprites/hero.png");
	heroSprite.setTexture(heroTexture);
	heroSprite.setOrigin(32, 128);
	heroSprite.setPosition(1280, 1360);
	sf::Vector2f velocity(sf::Vector2f(0, 0));
	sf::Vector2i anim(sf::Vector2i(0, 1));

	// Initialize basic hero stats
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
	heroSprite.move(velocity.x, 0.f);
	walkAnim();
}

void Hero::right()
{
	velocity.x = heroSpeed;
	heroSprite.move(velocity.x, 0.f);
	walkAnim();
}

void Hero::jump(float seconds)
{
	if (jumpTimer < 22 && jumpCooldown > 3)
	{
		velocity.y = -350;
		velocity.y += GRAVITY*seconds*jumpTimer*2;
		heroSprite.move(velocity*seconds);
		velocity.y = 0;
		jumpTimer++;
	}
	if (heroSprite.getPosition().y + heroSprite.getScale().y >= 1359)
	{
		jumpTimer = 0;
		jumpCooldown = 0;
	}
=======
	Texture.loadFromFile("../assets/sprites/hero.png"); 
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128);
	Sprite.setPosition(640, 640);
	
	// Initialize basic hero stats
	HP = HERO_BASE_HP;
	SpeedMultiplier = 1;
	Speed = HERO_BASE_SPEED * SpeedMultiplier;
<<<<<<< HEAD
>>>>>>> 9f8d7c0... Entity
=======
	isAlive = true;
>>>>>>> 3354455... Added/Modified Entity, Hero, Enemies, Enemy1, and Enemy2
}

void Hero::update(float seconds)
{
<<<<<<< HEAD
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
		if (heroSprite.getPosition().y + heroSprite.getScale().y < 1350) //This should later be changed to a collision with groud boolean
		{
			velocity.y += GRAVITY * seconds * seconds*50;
			heroSprite.move(0.f, velocity.y);
		}
		else
		{
			velocity.y = 0;
			if (jumpCooldown < 4)
				jumpCooldown++;
			heroSprite.setPosition(heroSprite.getPosition().x, 1360);
		}
	}
=======
	// Handle movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		left();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		right();

	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		jump();

	// Check if alive
	if (HP <= 0)
		isAlive = false;
>>>>>>> 9f8d7c0... Entity
}

void Hero::onHit(int dmg)
{
<<<<<<< HEAD
<<<<<<< HEAD
	heroSprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 128, 64, 128));
	window.draw(heroSprite);
=======
	window.draw(Sprite);
>>>>>>> 9f8d7c0... Entity
}
=======
	//armor and stuff
}
>>>>>>> 3354455... Added/Modified Entity, Hero, Enemies, Enemy1, and Enemy2

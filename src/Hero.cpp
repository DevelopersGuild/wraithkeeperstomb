#include "Hero.h"
#include "Constants.h"

Hero::Hero()
{
	// Load hero texture, assign to sprite, set starting sprite dimensions
	heroTexture.loadFromFile("../assets/sprites/hero.png");
	heroSprite.setTexture(heroTexture);
	heroSprite.setOrigin(32, 128);
	heroSprite.setPosition(1280, 1360);
	sf::Vector2f velocity(sf::Vector2f(0, 0));
	sf::Vector2i direct(sf::Vector2i(faceRight, 1));

	// Initialize basic hero stats
	heroHP = HERO_BASE_HP;
	isAlive = true;
	heroSpeedMultiplier = 1;
	heroSpeed = HERO_BASE_SPEED * heroSpeedMultiplier;
	jumpTimer = 0; //Timer for jump function duration
	jumpCooldown = 0;
}

void Hero::left()
{
	velocity.x = -heroSpeed;
	heroSprite.move(velocity.x, 0.f);
}

void Hero::right()
{
	velocity.x = heroSpeed;
	heroSprite.move(velocity.x, 0.f);
}

void Hero::jump(float seconds)
{
	if (jumpTimer < 20 && jumpCooldown > 2)
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
}

void Hero::update(float seconds)
{
	if (jumpTimer != 0)
		jump(seconds);
	{
		// Handle movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			direct.x = faceLeft;
			left();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			direct.x = faceRight;
			right();
		}
		else
			velocity.x = 0;

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
			if (jumpCooldown > 2)
				jumpCooldown = 3;
			else
				jumpCooldown++;
			heroSprite.setPosition(heroSprite.getPosition().x, 1360);
		}
	}
}

void Hero::render(sf::RenderWindow &window)
{
	heroSprite.setTextureRect(sf::IntRect(direct.x * 64, direct.y * 128, 64, 128));
	window.draw(heroSprite);
}
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
	velocity.y = -1400;
	heroSprite.move(velocity*seconds);
	velocity.y = 0;
}

void Hero::update(float seconds)
{
	// Handle movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direct.x = faceLeft;
		left();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direct.x = faceRight;
		right();
	}
	else
		velocity.x = 0;

	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		jump(seconds);

	// Check if alive
	if (heroHP <= 0)
		isAlive = false;

	//Gravity implementation
	if (heroSprite.getPosition().y + heroSprite.getScale().y < 1350) //This should later be changed to a collision with groud boolean
	{
		velocity.y += GRAVITY * seconds;
		heroSprite.move(0.f, velocity.y);
	}
	else
	{
		velocity.y = 0;
		heroSprite.setPosition(heroSprite.getPosition().x, 1360);
	}
}

void Hero::render(sf::RenderWindow &window)
{
	heroSprite.setTextureRect(sf::IntRect(direct.x * 64, direct.y * 128, 64, 128));
	window.draw(heroSprite);
}
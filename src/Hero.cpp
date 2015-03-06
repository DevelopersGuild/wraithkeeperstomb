#include "Hero.h"
#include "Spear.h"

#include "Constants.h"
#include <ctime>

Hero::Hero()
{
	// Load hero texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile("../assets/sprites/hero.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128);
	Sprite.setPosition(280, 1360);
	sf::Vector2f velocity(sf::Vector2f(0, 0));
	sf::Vector2i anim(sf::Vector2i(0, 1));

	// Initialize basic hero stats
	level_ = HERO_BASE_LEVEL;
	experience_ = 0;
	armor = HERO_BASE_ARMOR;
	HP = HERO_BASE_HP;
	is_alive_ = true;
	speedMultiplier = 1;
	speed = HERO_BASE_SPEED * speedMultiplier;
	jumpTimer = 0; //Timer for jump function duration
	jumpCooldown = 0;
	xFrame = 0;
	yFrame = 0;
	frameTimer = 0;
	faceRight = true;

	srand((unsigned int)time(NULL));
	giveWeapon(new Spear(this));
}

void Hero::setCollisionNum(int somethingUnderneath){
	collisionNum = somethingUnderneath;
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
	velocity.x = -speed;
	Sprite.move(velocity.x, 0.f);
	walkAnim();
}

void Hero::right()
{
	velocity.x = speed;
	Sprite.move(velocity.x, 0.f);
	walkAnim();
}

void Hero::jump(float seconds)
{
	if (jumpTimer < 22 && jumpCooldown > 3)
	{
		velocity.y = -1050;
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
		if (HP <= 0)
			is_alive_ = false;

		//Gravity implementation
		if (Sprite.getPosition().y + Sprite.getScale().y < 1350 || collisionNum == 0) //This should later be changed to a collision with groud boolean
		{
			velocity.y += GRAVITY * seconds * seconds * 50 * collisionNum;
			Sprite.move(0.f, velocity.y);
			if (collisionNum == 0){
				jumpTimer = 0;
			}
		}
		else
		{
			
			velocity.y = 0;
			if (jumpCooldown < 4)
				jumpCooldown++;
			Sprite.setPosition(Sprite.getPosition().x, 1360);
		}
	}
	if (weapon != 0)
	{
		//weapon->update(this, static_cast<Entity *>(NULL));
		weapon->setPosition(getX(), getY());
	}
}

void Hero::render(sf::RenderWindow &window)
{
	if (is_alive_){
		Sprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 128, 64, 128));
		window.draw(Sprite);
		if (weapon != 0){
			weapon->render(window);
		}
	}
}

void Hero::onHit(float dmg)
{
	if (dmg > armor)
		HP = HP - (dmg - armor / 4 + rand() % 3);
	else
		HP = HP - rand() % 5;
}



void Hero::setExperience(int add_exp)
{
	experience_ += add_exp;
	while (experience_ >= 100 * level_)
	{
		++level_;
		experience_ -= 100 * level_;
	}
}

void Hero::giveWeapon(Weapons * newWeapon)
{
	if (weapon != 0)
	{
		delete weapon;
	}
	weapon = newWeapon;
}
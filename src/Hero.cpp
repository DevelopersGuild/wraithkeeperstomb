#include "Hero.h"
#include "Constants.h"
#include "Spear.h"
#include <ctime>
#include <iostream>

Hero::Hero()
{
	// Load hero texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile("../assets/sprites/hero.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128);
	Sprite.setPosition(720, 1360);
	sf::Vector2f velocity(sf::Vector2f(0, 0));
	sf::Vector2i anim(sf::Vector2i(0, 1));
	invincibilityCD.restart();

	// Initialize basic hero stats
	stats_.level_ = HERO_BASE_LEVEL;
	stats_.experience_ = 0;
	stats_.armor = HERO_BASE_ARMOR;
	stats_.HP = HERO_BASE_HP;
	is_alive_ = true;
	stats_.speedMultiplier = 1;
	stats_.speed = HERO_BASE_SPEED * stats_.speedMultiplier;
	jumpTimer = 0; //Timer for jump function duration
	jumpCooldown = 0;
	xFrame = 0;
	yFrame = 0;
	frameTimer = 0;
	faceRight = true;

	effects_.push_back(new Buff(10, 7.0F)); //gives 10 sec boost at the beginning of game

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
	velocity.x = -stats_.speed;
	Sprite.move(velocity.x, 0.f);
	walkAnim();
}

void Hero::right()
{
	velocity.x = stats_.speed;
	Sprite.move(velocity.x, 0.f);
	walkAnim();
}

bool Hero::attack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		if(weapon->attack())
			return true;
	return false;
}
/*
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
*/

void Hero::jump(float seconds){
	
	collisionNum = 1;
		velocity.y = -32;

		if (collisionNum == 2){
			velocity.y = 0;
		}
		if (velocity.y < 0){
			Sprite.move(velocity);
			velocity.y += GRAVITY;
		}
	
	
}
void Hero::update(float seconds)
{
	/*for (auto &iter = effects_.begin(); iter != effects_.end();) {
		if ((*iter)->HasTimedOut())
		{
			delete *iter;
			iter = effects_.erase(iter);
			stats_.speed = HERO_BASE_SPEED * stats_.speedMultiplier;
		}
		else {
			stats_.speed = HERO_BASE_SPEED * stats_.speedMultiplier;
			(*iter)->UpdateAndApply(seconds, &stats_.speed);
			++iter;
		}
	}*/

	//prevent bonuses from increasing over time
	stats_.speed = HERO_BASE_SPEED * stats_.speedMultiplier;

	for (int i = 0; i < effects_.size(); i++) //iterate through all buffs/debuffs
	{
		if (effects_[i]->HasTimedOut())
		{//when duration of a buff/debuff expires
			delete effects_[i];
			effects_.erase(effects_.begin() + i);
		}
		else
		{//apply & keeps track on how long a buff/debuff has lasted
			effects_[i]->UpdateAndApply(seconds, &stats_.speed);
		}
	}


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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (Sprite.getPosition().y == 1360 || collisionNum == 0))
			jump(seconds);
			//jump(seconds);

		// Check if alive
		if (stats_.HP <= 0)
			is_alive_ = false;

		//Gravity implementation
		if (Sprite.getPosition().y + Sprite.getScale().y < 1350)// || collisionNum == 0) //This should later be changed to a collision with groud boolean
		{
			velocity.y += GRAVITY * seconds * seconds * 265 * collisionNum;
			Sprite.move(0.f, velocity.y);
			
			if (collisionNum == 0){
				velocity.y = 0;

			}
		}
		else
		{
			velocity.y = 0;
			//if (jumpCooldown < 4)
				//jumpCooldown++;
			Sprite.setPosition(Sprite.getPosition().x, 1360);
		}
	}
	if (weapon != 0)
	{
		//weapon->update(this, static_cast<Entity *>(NULL));
		weapon->setPosition(getX(), getY());
		weapon->update();
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
	if (invincibilityCD.getElapsedTime().asSeconds() > 1)
	{
		invincibilityCD.restart();
		if (dmg > stats_.armor)
			stats_.HP = stats_.HP - (dmg - stats_.armor / 3 + rand() % 3);
		else
			stats_.HP = stats_.HP - rand() % 5;
	}
}



void Hero::setExperience(int add_exp)
{
	stats_.experience_ += add_exp;
	while (stats_.experience_ >= 100 * stats_.level_)
	{
		++stats_.level_;
		stats_.experience_ -= 100 * stats_.level_;
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

void Hero::knockBack(Entity *hitter)
{
	if ((getX() - hitter->getX()) <= 1)
	{
		velocity.x = -stats_.speed;
		Sprite.move((3 * velocity.x), 0.f);
	}
	else
	{
		velocity.x = stats_.speed;
		Sprite.move((3 * velocity.x), 0.f);
	}
}

Hero::~Hero()
{
	for (auto &effect : effects_) {
		delete effect;
	}

	effects_.clear();
}
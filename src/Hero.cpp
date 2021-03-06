#include "Hero.h"
#include "Constants.h"
#include "Spear.h"
#include "Projectile.h"
#include "Paths.h"
#include <ctime>
#include <iostream>

Hero::Hero()
{
	// Load hero texture, assign to sprite, set starting sprite dimensions
	Texture.loadFromFile(resourcePath() + "assets/sprites/hero.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(32, 128);
	Sprite.setPosition(720, 1472);
	sf::Vector2f velocity(sf::Vector2f(0, 0));
	sf::Vector2i anim(sf::Vector2i(0, 1));
	invincibilityCD.restart();

	// Initialize basic hero stats
	stats_.level_ = HERO_BASE_LEVEL;
	stats_.experience_ = 0;
	stats_.armor = HERO_BASE_ARMOR;
	stats_.max_HP = HERO_BASE_HP; // Change after Save/Load is implemented
	stats_.HP = stats_.max_HP;
	stats_.MP = HERO_BASE_MP;
	is_alive_ = true;
	stats_.speedMultiplier = 1;
	stats_.speed = HERO_BASE_SPEED * stats_.speedMultiplier;
	atkTime = 0;
	jumpTimer = 0; //Timer for jump function duration
	jumpCooldown = 0;
	xFrame = 0;
	yFrame = 0;
	frameTimer = 0;
	faceRight = true;
	isFrozen = false;
	projectileCooldown = 0.0;
	collisionNum = 0;
	backing = 0;
	knockBackDuration = 0.1;
	atk_crit = false;
	isAttacking = false;

	atkframeTimer = 0;

	walkingSounds.loadFile(resourcePath() + "assets/sounds/footsteps.wav");

	srand((unsigned int)time(NULL));
	giveWeapon(new Spear(this));
}

void Hero::animate(int action)
{
	if (velocity.y != 0 && action != attacks)
		action = jumps;
	if (atkframeTimer > 17)
		atkframeTimer = 0;
	switch (action)
	{
	case stands:
		velocity.x = 0;
		xFrame = 0;
		anim.y = 0;
		if (frameTimer != 0 && action != attacks)
			frameTimer = 0;		
		if (faceRight)
			anim.x = 0;
		else
			anim.x = 1;
		break;
	case walks:
		if (velocity.y == 0)
			walkAnim();
		break;
	case jumps:
		jumpAnim();
		break;
	case attacks:
		attackAnim();
		break;
	case knockback:
		knockbackAnim();
		break;
	default:
		break;
	}
}

void Hero::walkAnim()
{
	//Determine row in sprite sheet
	if (faceRight)
		anim.y = 1;
	else
		anim.y = 2;
	//Move frame forward
	if (frameTimer > 5)
	{
		if (xFrame != 4 && xFrame != 9)
		{
			frameTimer = 0;
			xFrame++;
		}
		else if (frameTimer > 7)
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

void Hero::jumpAnim()
{
	if (faceRight)
		anim.y = 3;
	else
		anim.y = 4;
	//Move frame forward
	if (frameTimer < 3)
		xFrame = 0;
	else if (frameTimer < 7)
		xFrame = 1;
	else
		xFrame = 2;

	anim.x = xFrame;
	frameTimer++;
}

void Hero::attackAnim()
{
	if (faceRight)
	{
		anim.y = 5;
		velocity.x = 2;
		yFrame = 1;
	}
	else
	{
		anim.y = 6;
		velocity.x = -2;
		yFrame = -1;
	}
	//Move frame forward
	if (atkframeTimer < 2)
	{
		xFrame = 0;
		weapon->setPosition(getX() + 17 * yFrame, getY() - 14);
	}
	else if (atkframeTimer < 3)
	{
		xFrame = 1;
		Sprite.move(velocity.x * .5f, 0.f);
		weapon->setPosition(getX() + 23 * yFrame, getY() - 10);
	}
	else if (atkframeTimer < 6)
	{
		xFrame = 2;
		Sprite.move(velocity.x * .7f, 0.f);
		weapon->setPosition(getX() + 28 * yFrame, getY() - 8);
	}
	else if (atkframeTimer < 14)
	{
		xFrame = 3;
		weapon->setPosition(getX() + 39 * yFrame, getY() - 8);
	}
	else
	{
		xFrame = 0;
		Sprite.move(velocity.x * .02f, 0.f);
		weapon->setPosition(getX() + 12 * yFrame , getY() - 14);
	}
	anim.x = xFrame;
	atkframeTimer++;
	if (weapon != 0)
		weapon->update(faceRight);
	atkTime--;

	if (atkTime == 0)
		isAttacking = false;
}

void Hero::knockbackAnim()
{
	if (faceRight)
		anim.y = 3;
	else
		anim.y = 4;
	xFrame = 2;
}

void Hero::left()
{
	velocity.x = -stats_.speed;
	if (velocity.y == 0)
		action = walks;
	else
		anim.x = xFrame = 0;
}

void Hero::right()
{
	velocity.x = stats_.speed;
	if (velocity.y == 0)
		action = walks;
	else
		anim.x = xFrame = 0;
}

bool Hero::attack()
{
	if (weapon->attack())
	{
		atk_crit = weapon->getCritStatus();
		atkTime = 18;
		freezeHero(freezeClock);
		return true;
	}
	return false;
} 

void Hero::freezeHero(sf::Clock &freezeClock)
{
	isFrozen = true;
	freezeClock.restart().asSeconds();
}

void Hero::unfreezeHero(sf::Clock freezeClock, float time)
{
	if (freezeClock.getElapsedTime().asSeconds() >= time)
		isFrozen = false;
}

bool Hero::projectileShoot()
{
	if (stats_.MP <= 0) return false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))// && velocity.y == 0)
		if (projectileCooldown <= 0.0)
		{
			//magic cast animation
			return true;
		}
	return false;
}

void Hero::consumeMP(float cost)
{
	stats_.MP -= cost;
}

void Hero::jump(float seconds)
{
	if (action != attacks)
	{
		collisionNum = 1;
		velocity.y = -HERO_JUMP_VELOCITY;

		if (collisionNum == 2){
			velocity.y = 0;
		}
		if (velocity.y < 0 && !isFrozen){
			velocity.y += GRAVITY;
			Sprite.move(velocity);
		}
	}
}

void Hero::handleEvent(sf::Event & event) {
	if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Q))
	{
		if (attack() && isAttacking == false)
			isAttacking = true;
	}
}

void Hero::update(float seconds)
{
	//prevent bonuses from increasing over time
	stats_.speed = HERO_BASE_SPEED * stats_.speedMultiplier;
	for (auto iter = effects_.begin(); iter != effects_.end();) { //iterate through all buffs/debuffs 
		if ((*iter)->HasTimedOut())
		{ //when duration of a buff/debuff expires
			delete *iter;
			iter = effects_.erase(iter); // returns the next iterator
		}
		else { //apply & keeps track on how long a buff/debuff has lasted
			if (dynamic_cast<Debuff*>(*iter)) {
				(*iter)->UpdateAndApply(seconds, &stats_.HP);
			}
			else
				(*iter)->UpdateAndApply(seconds, &stats_.speed);
			++iter;
		}
	}
	unfreezeHero(freezeClock, 0.3f);
	{
		// Handle movement
		walkingSounds.playSound();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !isFrozen)
		{
			faceRight = false;
			left();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !isFrozen)
		{
			faceRight = true;
			right();
		}
		else if (backing != 0)
			action = knockback;
		else
		{
			walkingSounds.stopSound();
			action = stands;
		}

		// Jump
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && collisionNum == 0 && !isFrozen)
			jump(seconds);

		// Check if alive
		if (stats_.HP <= 0)
			is_alive_ = false;

		knockBack(seconds);
		doPhysics(seconds);

		if (velocity.y != 0)
		{
			action = jumps;
		}
	}
	if (weapon != 0)
	{
		if (atkTime == 0 && faceRight)
		{
			weapon->setPosition(getX() + 26, getY() - 54);
		}
		else if (atkTime == 0 && !faceRight)
		{
			weapon->setPosition(getX() - 26, getY() - 54);
		}
		weapon->update(faceRight);
	}

	if (projectileCooldown > 0)
		projectileCooldown -= seconds;

	if (getY() > 1372.f)
		setPosition(getX(), GROUND_HEIGHT + 12.f);

	if (stats_.MP < 100)
		stats_.MP += seconds;
}

void Hero::render(sf::RenderWindow &window)
{

	
	if (is_alive_)
	{
		if (atkTime > 0)
			animate(attacks);
		else
			animate(action);
		Sprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 128, 64, 128));

		window.draw(Sprite);
		if (weapon != 0 && atkTime == 0)
		{
			window.draw(Sprite);
			if (!faceRight)
			{
				weapon->rotateWeapon(70);
			}
			else
			{
				weapon->rotateWeapon(-70);
			}
			weapon->render(window);
			window.draw(Sprite);
		}
		else
		{
			weapon->rotateWeapon(0);
			weapon->render(window);
			window.draw(Sprite);

		}
	}
}

float Hero::onHit(float dmg)
{
	if (dmg < 0)
		return dmg;
	if (invincibilityCD.getElapsedTime().asSeconds() > 1)
	{
		float dmgDealt = 0;
		invincibilityCD.restart();
		if (dmg > stats_.armor)
			dmgDealt = dmg - stats_.armor / 3 + rand() % 3;
		else
			dmgDealt = rand() % 5;

		stats_.HP = stats_.HP - dmgDealt;
		return dmgDealt;
	}
	else
		return 0;
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
	if (weapon != 0) delete weapon;
	weapon = newWeapon;
}

void Hero::knockBack(float seconds)
{
	if (backing != 0)
	{
		if (backing == 'l')
		{
			velocity.x = -stats_.speed * seconds * seconds * 1000;
			Sprite.move((4.5 * velocity.x), 0.f);
		}
		else if (backing == 'r')
		{
			velocity.x = stats_.speed * seconds * seconds * 1000;
			Sprite.move((4.5 * velocity.x), 0.f);
		}
		else
		{
			velocity.x = -stats_.speed * seconds * seconds * 1000;
			Sprite.move((4.5 * velocity.x), 0.f);
		}
		knockBackDuration -= seconds;
		isFrozen = true;
	}
	else
	{
	}
	if (knockBackDuration < 0)
	{
		backing = 0;
		knockBackDuration = 0.1;
		isFrozen = false;
	}
}

const sf::FloatRect Hero::getCollisionRect()
{
	sf::FloatRect bigBox = Sprite.getGlobalBounds();
	return sf::FloatRect(bigBox.left + 15.5f, bigBox.top + 23.f, bigBox.width - 31.f, bigBox.height - 23.f);
}

void Hero::setPosition(float x, float y)
{
	Sprite.setPosition(x, y);

	if (weapon && faceRight && atkTime == 0)
		weapon->setPosition(x + 26, y - 54);
	else if (weapon && !faceRight && atkTime == 0)
		weapon->setPosition(x - 26, y - 54);
}

void Hero::heal(float healAmt)
{
	stats_.HP += healAmt;
	if (stats_.HP > stats_.max_HP)
		stats_.HP = stats_.max_HP;
}

Hero::~Hero()
{
	for (auto &effect : effects_)
		delete effect;

	delete weapon;

	effects_.clear();
}

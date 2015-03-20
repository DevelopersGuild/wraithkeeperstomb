#ifndef HERO_H
#define HERO_H

#include <list>

#include "Entity.h"
#include "Effect.h"
#include "Weapons.h"

#include <SFML/Graphics.hpp>

typedef Hero Hero;

class Hero : public Entity
{
private:
	sf::Vector2i anim;		//Tracker for hero sprite frames
	sf::Clock invincibilityCD;

	struct {
		float speed;
		float speedMultiplier;

		float armor;
		float HP;

		float heroJumpSpeed;
		int level_;

		int experience_;
	} stats_;

	Weapons *weapon = NULL;

	sf::Clock jumpClock;

	enum {stands, walks, jumps, attacks};
	int action;

	int xFrame;					//Current frame in the x grid
	int yFrame;					//Current frame in the y grid
	int frameTimer;				//Counter for sprite frame duration
	int atkTime;
	float jumpCooldown;			//Cooldown counter for jump
	float jumpTimer;				//Counter for jump duration
	bool faceRight;				//Boolean for determining direction hero is facing at rest
	bool inAir;


	std::list<Effect*> effects_;

	void animate(int);		//Function for handling animations
	void walkAnim();		//Animation sequence for walking
	void jumpAnim();		//Animation sequence for jumping
	void attackAnim();		//Animation sequence for attacking
	//void jump(float seconds);
public:
	Hero();
	~Hero();
	void update(float seconds);
	void render(sf::RenderWindow &window);
	void onHit(float dmg);
	bool attack();
	void jump(float seconds);
	void left();
	void right();
	void setExperience(int add_exp);

	void setLevel(int level) { stats_.level_ = level; }
	void setHP(float hp) { stats_.HP = hp; }


	void giveWeapon(Weapons * weapon);

	void freeze() {}
	void knockBack(Entity *hitter);

	virtual void setPosition(float x, float y);

	// Accessors
	bool getFaceRight() const
	{ return faceRight; }

	float getSpeedX() const
	{ return velocity.x; }

	float getSpeedY() const
	{ return velocity.y; }

	float getHP() const
	{ return stats_.HP; }

	int getLevel() const 
	{ return stats_.level_; }

	int getExperience() const
	{ return stats_.experience_; }


	sf::Sprite getHeroSprite()
	{ return Sprite; }

	const sf::FloatRect getDamagingRect()
	{ return weapon->getAttackRect(faceRight); }

	const float getDamage()
	{ return weapon->getDamage(); }

	void update();
};

#endif
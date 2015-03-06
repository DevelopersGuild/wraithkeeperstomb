#ifndef HERO_H
#define HERO_H

#include "Entity.h"
#include "Effect.h"
#include "Weapons.h"


#include <SFML/Graphics.hpp>

class Hero : public Entity
{
private:
	sf::Vector2f velocity;
	sf::Vector2i anim;		//Tracker for hero sprite frames


	struct {
		float speed;
		float speedMultiplier;

		float armor;
		int HP;

		float heroJumpSpeed;
		int level_;

		int experience_;
	} stats_;

	Weapons *weapon = NULL;

	int collisionNum;

	int xFrame;					//Current frame in the x grid
	int yFrame;					//Current frame in the y grid
	int frameTimer;				//Counter for sprite frame duration
	float jumpCooldown;			//Cooldown counter for jump
	float jumpTimer;				//Counter for jump duration
	bool faceRight;				//Boolean for determining direction hero is facing at rest
	bool inAir;

	//struct {
	//	std::vector<Buff*> buffs;
	//	std::vector<Debuff*> debuffs;
	//} effects_;

	std::vector<Effect*> effects_;


	void walkAnim();			//Animation sequence for walking
	void jump(float seconds);
public:
	Hero();
	void update(float seconds);
	void render(sf::RenderWindow &window);
	void onHit(float dmg);
	void jump();
	void left();
	void right();
	void setCollisionNum(int);
	void setExperience(int add_exp);

	void setLevel(int level) { stats_.level_ = level; }
	void setHP(int hp) { stats_.HP = hp; }


	void giveWeapon(Weapons * weapon);

	// Accessors
	const float getSpeedX()
	{
		return velocity.x;
	}

	const float getSpeedY()
	{
		return velocity.y;
	}

	const int getHP()
	{
		return stats_.HP;
	}

	const int getLevel() {
		return stats_.level_;
	}

	const int getExperience()
	{ return stats_.experience_; }



	sf::Sprite getHeroSprite()
	{
		return Sprite;
	}

	void update();
};

#endif
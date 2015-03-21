#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Weapons.h"

class Projectile: public Weapons
{
protected:
	void flightAnim();
	int castTime;
	float speed;
	bool shot_by_hero;
	float cooldownDuration;
public:
	Projectile(float, float, bool);
	Projectile(float, float, bool, bool) {}//won't be called anyway
	virtual ~Projectile();
	//accessors
	const float getCooldownDuration() { return cooldownDuration; }
	const sf::Sprite getSprite()
	{
		return Sprite;
	}
	const sf::FloatRect getCollisionRect();
	bool is_shot_by_hero() { return shot_by_hero; }
	const sf::FloatRect getAttackRect();

	void update();
	bool attack();
	bool overRange();
};

class HolyOrb : public Projectile
{
private:
	//special features?
public:
	HolyOrb(float a, float b, bool c, bool faceRight) : Projectile(a, b, c)
	{
		Texture.loadFromFile("../assets/sprites/holyorb.png");
		Sprite.setTexture(Texture);

		cooldownDuration = HOLYORB_COOLDOWN;
		damage = HOLYORB_DAMAGE;
		range = HOLYORB_RANGE; //actually is distance left
		crit_chance = HOLYORB_CRIT_CHANCE;
		crit_multiplier = HOLYORB_CRIT_MULTIPLIER;
		damage_fluctuation = HOLYORB_DMG_FLUCTUATION_RATE * HOLYORB_DAMAGE;
		damage = dmgRandomizer(damage_fluctuation) * critical(crit_multiplier);

		if (faceRight)
			speed = HOLYORB_SPEED;
		else
			speed = -HOLYORB_SPEED;
	}
	~HolyOrb(){}
};

class FireBall : public Projectile
{
private:
	//special features?
public:
	FireBall(float a, float b, bool c, bool faceRight) : Projectile(a, b, c)
	{
		Texture.loadFromFile("../assets/sprites/fireball.png");
		Sprite.setTexture(Texture);

		cooldownDuration = FIREBALL_COOLDOWN;
		damage = FIREBALL_DAMAGE;
		range = FIREBALL_RANGE; //actually is distance left
		crit_chance = FIREBALL_CRIT_CHANCE;
		crit_multiplier = FIREBALL_CRIT_MULTIPLIER;
		damage_fluctuation = FIREBALL_DMG_FLUCTUATION_RATE * FIREBALL_DAMAGE;
		damage = dmgRandomizer(damage_fluctuation) * critical(crit_multiplier);

		if (faceRight)
			speed = FIREBALL_SPEED;
		else
			speed = -FIREBALL_SPEED;
	}
	~FireBall(){}
};

#endif
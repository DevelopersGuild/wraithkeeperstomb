#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Weapons.h"
#include "Paths.h"

class Projectile: public Weapons
{
protected:
	void flightAnim();
	int castTime;
	float speed;
	bool shot_by_hero;//temporary solution until HeroProjectile
	float cooldownDuration;
	float mana_cost;//remove to HeroProjectile when done
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
	virtual float getManaCost() { return 0; }

	void update();
	bool attack();
	bool overRange();
};
//PLAN: HeroProjectile and EnemyProjectile children classes
class HolyOrb : public Projectile
{
private:
	//special features?
public:
	HolyOrb(float shooter_x, float shooter_y, bool shot_by_hero, bool faceRight)
		: Projectile(shooter_x, shooter_y, shot_by_hero)
	{
		Texture.loadFromFile(resourcePath() + "assets/sprites/holyorb.png");
		Sprite.setTexture(Texture);

		cooldownDuration = HOLYORB_COOLDOWN;
		mana_cost = HOLYORB_MANA_COST;
		damage = HOLYORB_DAMAGE;
		range = HOLYORB_RANGE; //actually is distance left
		crit_chance = HOLYORB_CRIT_CHANCE;
		crit_multiplier = HOLYORB_CRIT_MULTIPLIER;
		damage_fluctuation = HOLYORB_DMG_FLUCTUATION_RATE * HOLYORB_DAMAGE;
		damage = dmgRandomizer(damage_fluctuation) * critical(crit_multiplier);

		if (faceRight)
			speed = HOLYORB_SPEED;
		else
		{
			Sprite.setScale(-1.f, 1.f);
			speed = -HOLYORB_SPEED;
		}
	}
	~HolyOrb(){}
	float getManaCost() { return mana_cost; }
};

class FireBall : public Projectile
{
private:
	//special features?
public:
	FireBall(float shooter_x, float shooter_y, bool shot_by_hero, bool faceRight)
		: Projectile(shooter_x, shooter_y, shot_by_hero)
	{
		Texture.loadFromFile(resourcePath() + "assets/sprites/fireball.png");
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
		{
			Sprite.setScale(-1.f, 1.f);
			speed = -FIREBALL_SPEED;
		}
	}
	~FireBall(){}
};

#endif

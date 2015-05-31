#include "Entity.h"
#include "Constants.h"
#include "Hero.h"
#include "Spear.h"
#include "Game.h"
#include "Paths.h"

//powerup
class Powerup : public Entity
{
public:
	Powerup();

	void update(float time);

	void render(sf::RenderWindow &window);

	virtual void apply(Hero * hero) = 0;

	void freeze(){};
	void backDirection(float, float){};
	void knockBack(float){};
};

class PowerupCookie : public Powerup
{
public:
	PowerupCookie()
	{
		Texture.loadFromFile(resourcePath() + "assets/sprites/cookie.png");
		Sprite.setTexture(Texture);
		Sprite.setOrigin(0, 0);
		Sprite.setPosition(500.f, 800.f);
	}

	void apply(Hero * hero)
	{
		hero->setHP(HERO_BASE_HP);
	}
};

class PowerupSpear : public Powerup
{
public:
	PowerupSpear()
	{
		Texture.loadFromFile(resourcePath() + "assets/sprites/spear2.png");
		Sprite.setTexture(Texture);
		Sprite.setOrigin(0, 0);
		Sprite.setPosition(500.f, 800.f);
		Sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));


	}

	void apply(Hero * hero)
	{
		Game::getHero()->giveWeapon(new Spear2(Game::getHero()));
	}

};

class PowerupCoffee : public Powerup
{
public:
	PowerupCoffee()
	{
		Texture.loadFromFile(resourcePath() + "assets/sprites/speedBoost.png");
		Sprite.setTexture(Texture);
		Sprite.setOrigin(0, 0);
		Sprite.setPosition(500.f, 800.f);
	}
	void apply(Hero *hero)
	{
		
	}
};

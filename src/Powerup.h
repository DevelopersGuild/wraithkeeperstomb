#include "Entity.h"
#include "Constants.h"
#include "Hero.h"
#include "Spear.h"
#include "Game.h"

//powerup
class Powerup : public Entity
{
public:
	Powerup();

	void update(float time);

	void render(sf::RenderWindow &window);

	virtual void apply(Hero * hero) = 0;

};

class PowerupCookie : public Powerup
{
public:
	PowerupCookie()
	{
		Texture.loadFromFile("../assets/sprites/cookie.png");
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
		Texture.loadFromFile("../assets/sprites/spear1.png");
		Sprite.setTexture(Texture);
		Sprite.setOrigin(0, 0);
		Sprite.setPosition(500.f, 800.f);
	}

	void apply(Hero * hero)
	{
		Game::getHero()->giveWeapon(new Spear(Game::getHero()));
	}

};
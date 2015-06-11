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
	virtual void effectTextAppears() {};
};

class PowerupCookie : public Powerup
{
public:
	PowerupCookie()
	{
		Texture.loadFromFile(resourcePath() + "assets/sprites/cookie.png");
		lato.loadFromFile(resourcePath() + "assets/fonts/lato.ttf");
		Sprite.setTexture(Texture);
		Sprite.setOrigin(0, 0);
		Sprite.setPosition(500.f, 800.f);

		effectText.setFont(lato);
		effectText.setCharacterSize(19);
		effectText.setString("");
		effectText.setColor(sf::Color::Green);
		is_alive_ = true;
		
		healAmt = HERO_BASE_HP;
	}

	void apply(Hero * hero)
	{
		hero->heal(healAmt);
	}

	void effectTextAppears()
	{
		effectText.setPosition(Sprite.getPosition().x, Sprite.getPosition().y - 75);
		effectText.setString("+" + std::to_string(static_cast<int>(healAmt)));
	}

private:
	float healAmt;
};

class PowerupSpear : public Powerup
{
public:
	PowerupSpear()
	{
		Texture.loadFromFile(resourcePath() + "assets/sprites/spear2.png");
		lato.loadFromFile(resourcePath() + "assets/fonts/lato.ttf");
		Sprite.setTexture(Texture);
		Sprite.setOrigin(0, 0);
		Sprite.setPosition(500.f, 800.f);
		Sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

		effectText.setFont(lato);
		effectText.setCharacterSize(19);
		effectText.setString("");
		effectText.setColor(sf::Color::Cyan);

		is_alive_ = true;
	}

	void apply(Hero * hero)
	{
		Game::getHero()->giveWeapon(new Spear2(Game::getHero()));
	}

	void effectTextAppears()
	{
		effectText.setPosition(Sprite.getPosition().x, Sprite.getPosition().y - 75);
		effectText.setString("Weapon upgraded");
	}
};

class PowerupCoffee : public Powerup
{
public:
	PowerupCoffee()
	{
		Texture.loadFromFile(resourcePath() + "assets/sprites/speedBoost.png");
		lato.loadFromFile(resourcePath() + "assets/fonts/lato.ttf");
		Sprite.setTexture(Texture);
		Sprite.setOrigin(0, 0);
		Sprite.setPosition(500.f, 800.f);

		effectText.setFont(lato);
		effectText.setCharacterSize(19);
		effectText.setPosition(Sprite.getPosition().x, Sprite.getPosition().y - 75);
		effectText.setString("");
		effectText.setColor(sf::Color::Blue);
	}
	void apply(Hero *hero)
	{
		
	}
};

#include "Entity.h"
#include "Constants.h"
#include "Hero.h"

//powerup
class Powerup : public Entity
{
public:
	Powerup(float posX, float posY, float sizeX, float sizeY);

	void update(float time);

	void render(sf::RenderWindow &window);

	virtual void apply(Hero * hero) = 0;

};

class PowerupCookie : public Powerup
{
public:
	PowerupCookie(float posX, float posY) :Powerup(posX, posY, 64, 64)
	{
		Texture.loadFromFile("../assets/sprites/cookie.png");
	}

	void apply(Hero * hero)
	{
		hero->setHP(HERO_BASE_HP);
	}
};
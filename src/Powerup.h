#include "Entity.h"

//powerup
class Powerup : public Entity
{
public:
	Powerup(float posX, float posY, float sizeX, float sizeY);

	void update(float time);

	void render(sf::RenderWindow &window);

	virtual void apply(Hero * hero) = 0;

};
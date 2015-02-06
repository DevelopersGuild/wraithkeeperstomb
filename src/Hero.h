#ifndef HERO_H
#define HERO_H
#include "Entity.h"

#include <SFML/Graphics.hpp>

class Hero : public Entity
{
private:

public:
	Hero();
	void update();
	void render(sf::RenderWindow& window);

};

#endif

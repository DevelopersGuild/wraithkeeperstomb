#include "Door.h"
#include "Hero.h"
#include "Paths.h"

Door::Door()
{
	//isOpen = false;
	open_texture.loadFromFile(resourcePath() + "assets/sprites/opendoor.png");
	closs_texture.loadFromFile(resourcePath() + "assets/sprites/clossdoor.png");
	//closs_texture.setRepeated(true);
	sprite.setTexture(closs_texture);
	sprite.setPosition(1260, 1290);
}

void Door::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Door::setTexture(bool status)
{
	if (status)
		sprite.setTexture(open_texture);
	else
		sprite.setTexture(closs_texture);
}

Door::~Door()
{
}

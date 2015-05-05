#include "Door.h"
#include "Hero.h"
#include "Paths.h"

Door::Door()
{
	isOpen = false;

	texture.loadFromFile(resourcePath() + "assets/sprites/clossdoor.png");
	texture.setRepeated(true);
	sprite.setTexture(texture);
	sprite.setPosition(1260, 1290);

}

void Door::openDoor()
{
	isOpen = true;
	texture.loadFromFile(resourcePath() + "assets/sprites/opendoor.png");
	sprite.setTexture(texture);
}

void Door::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}


Door::~Door()
{
}

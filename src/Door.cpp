#include "Door.h"
#include "Hero.h"
#include "Paths.h"

Door::Door()
{
	//isOpen = false;

	closs_texture.loadFromFile("../assets/sprites/clossdoor.png");
	//closs_texture.setRepeated(true);
	sprite.setTexture(closs_texture);
	sprite.setPosition(1260, 1290);
}

bool Door::openDoor()
{
	open_texture.loadFromFile("../assets/sprites/opendoor.png");
	//open_texture.setRepeated(true);
	sprite.setTexture(open_texture);
	return true;
}

void Door::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}


Door::~Door()
{
}

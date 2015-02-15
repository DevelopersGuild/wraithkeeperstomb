#include "Platform.h"

Platform::Platform()
{
	setTexture();
}

Platform::Platform(sf::Vector2f nPos, sf::Vector2f nSize) : pos(nPos), size(nPos)
{
	setTexture();
	rec.setSize(size);
	rec.setPosition(pos);
}

void Platform::setSize(sf::Vector2f nSize)
{
	size = nSize;
	rec.setSize(size);
}

void Platform::setPosition(sf::Vector2f nPos)
{
	pos = nPos;
	rec.setPosition(pos);
}

void Platform::setTexture(){
	ground.loadFromFile("../assets/sprites/GroundTexture.png");
	ground.setRepeated(true);
	rec.setTexture(&ground);
	rec.setTextureRect({ 0, 0, 200, 32 });
}

void Platform::render(sf::RenderWindow &window)
{
	window.draw(rec);
}

Platform::~Platform()
{

}

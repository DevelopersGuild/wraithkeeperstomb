#include "Platform.h"


Platform::Platform()
{
	setColor();
}

Platform::Platform(sf::Vector2f nPos, sf::Vector2f nSize) : pos(nPos), size(nPos)
{
	setColor();
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


void Platform::setColor(sf::Color nColor)
{
	rec.setFillColor(nColor);
}


sf::Vector2f Platform::getPosition()
{
	return pos;
}


sf::Vector2f Platform::getSize()
{
	return size;
}


void Platform::render(sf::RenderWindow &window)
{
	window.draw(rec);
}

Platform::~Platform()
{

}

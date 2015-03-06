#include "Platform.h"

sf::Texture * platform_ground_texture = 0;

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
	if (platform_ground_texture == 0)
	{
		platform_ground_texture = new sf::Texture;
		platform_ground_texture->loadFromFile("../assets/sprites/GroundTexture.png");
		platform_ground_texture->setRepeated(true);
	}
	rec.setTexture(platform_ground_texture);
	rec.setTextureRect({ 0, 0, (int)(size.x/2), (int)(size.y/2) });
}

void Platform::render(sf::RenderWindow &window)
{
	window.draw(rec);
}

Platform::~Platform()
{

}

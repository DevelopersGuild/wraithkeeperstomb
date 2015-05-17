#include "Platform.h"
#include "Paths.h"

sf::Texture * platform_ground_texture = 0;
sf::Texture * ground_texture = 0;

Platform::Platform()
{
	
}

Platform::Platform(sf::Vector2f nPos, sf::Vector2f nSize, int type) : pos(nPos), size(nPos)
{
	setTexture(type);
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

void Platform::setTexture(int type){ //need texture for walls (borrowing from ground for now)

	if (platform_ground_texture == 0) {
		platform_ground_texture = new sf::Texture;
		platform_ground_texture->loadFromFile(resourcePath() + "assets/sprites/StonePlatform.png");
		platform_ground_texture->setRepeated(true);

	}
	if (ground_texture == 0)
	{
		ground_texture = new sf::Texture;
		ground_texture->loadFromFile(resourcePath() + "assets/sprites/StoneGround.png");
		ground_texture->setRepeated(true);

	}

	if (type == 0)
		rec.setTexture(platform_ground_texture);
	else if (type == 1)
		rec.setTexture(NULL);
	else if (type == 3)
		rec.setTexture(ground_texture);

	
	rec.setTextureRect({ 0, 0, (int)(size.x/2), (int)(size.y/2) });
}

void Platform::render(sf::RenderWindow &window)
{
	window.draw(rec);
}

Platform::~Platform()
{
	if (!platform_ground_texture)
	{
		delete platform_ground_texture;
		platform_ground_texture = 0;
	}
}

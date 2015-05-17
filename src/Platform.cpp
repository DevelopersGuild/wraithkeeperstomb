#include "Platform.h"
#include "Paths.h"

sf::Texture * platform_ground_texture = 0;
sf::Texture * ground_texture = 0;
sf::Texture * invisible_texture = 0;

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

	switch (type) {
	case 0: 
		if (platform_ground_texture == 0) {
			platform_ground_texture = new sf::Texture;
			platform_ground_texture->loadFromFile(resourcePath() + "assets/sprites/StonePlatform.png");
			platform_ground_texture->setRepeated(true);
		}
		rec.setTexture(platform_ground_texture);
		break;
	case 1: 
		rec.setTexture(NULL);
		break;
	case 2: 
		if (invisible_texture == 0) {
			invisible_texture = new sf::Texture;
			invisible_texture->loadFromFile(resourcePath() + "assets/sprites/blank.png");
			invisible_texture->setRepeated(true);
		}
		rec.setTexture(invisible_texture);
		break;
	case 3: 
		if (ground_texture == 0) {
			ground_texture = new sf::Texture;
			ground_texture->loadFromFile(resourcePath() + "assets/sprites/StoneGround.png");
			ground_texture->setRepeated(true);
		}
		rec.setTexture(ground_texture);
		break;
	}
	
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

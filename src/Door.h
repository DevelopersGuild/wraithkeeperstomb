#pragma once

#include <SFML/Graphics.hpp>

class Door
{
private:
	sf::Texture closs_texture;
	sf::Texture open_texture;
	sf::Sprite sprite;
//public:
	//bool isOpen;
public:
	Door();
	bool openDoor();
	void setPosition(float x, float y);
	//bool getOpen() { return isOpen; }

	sf::FloatRect getDoorRect() { return sprite.getGlobalBounds(); }
	sf::Sprite getSprite() { return sprite; }
	~Door();
};


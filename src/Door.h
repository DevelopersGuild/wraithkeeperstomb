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
	void setTexture(bool status); //0=closed, 1=open
	void setPosition(float x, float y);
	//bool getOpen() { return isOpen; }

	sf::FloatRect getDoorRect() { return sprite.getGlobalBounds(); }
	sf::Sprite getSprite() { return sprite; }
	~Door();
};


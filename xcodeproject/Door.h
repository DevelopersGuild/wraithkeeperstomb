#pragma once

#include <SFML/Graphics.hpp>

class Door
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	bool isOpen;
public:
	Door();
	void openDoor();
	void setPosition(float x, float y);
	sf::Sprite getSprite() { return sprite; }
	~Door();
};


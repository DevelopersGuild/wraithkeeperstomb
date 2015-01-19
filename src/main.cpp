#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Chamber's Labyrinth");
	sf::RectangleShape shape(sf::Vector2f(420.f, 420.f));
	shape.setFillColor(sf::Color::Cyan);
	shape.setOrigin(210.f, 210.f);
	shape.setPosition(640.f, 400.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}

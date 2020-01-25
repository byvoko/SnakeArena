#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
	sf::Vector2u windowSize(1200, 700);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SnakeArena");
	Game game(windowSize);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();

			game.ProcessEvent(event);
		}

		game.Update();
		game.Draw(window);
	}

	return 0;
}

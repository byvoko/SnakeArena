#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 700), "SnakeArena");
	Game game;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		game.Update();
		window.clear();
		game.Draw(window);
		window.display();
	}

	return 0;
}

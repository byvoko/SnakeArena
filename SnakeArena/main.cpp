#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Menu.hpp"

int main()
{
	bool pause = false;
	
	sf::Clock clockDraw;
	static constexpr int FPS = 60;

	sf::Vector2u windowSize(1200, 800);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SnakeArena");

	Game game(windowSize);
	Menu menu;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						window.close();
						break;
					case sf::Keyboard::P:
						pause = !pause;
						break;
				}
			}

			game.ProcessEvent(event);
		}

		if (!pause)
			game.Update();

		sf::Time elapsed = clockDraw.getElapsedTime();
		if (elapsed.asMilliseconds() < (1000 / FPS))
			continue;

		clockDraw.restart();
		game.Draw(window);
		if (pause)
			menu.Draw(window, {});
		window.display();
	}

	return 0;
}

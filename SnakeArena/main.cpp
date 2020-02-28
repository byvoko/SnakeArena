#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Menu.hpp"
#include "GameContext.hpp"

int main()
{
	sf::Clock clockDraw;
	static constexpr int FPS = 60;

	sf::Vector2u windowSize(1200, 800);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SnakeArena");

	GameContext gameContext(windowSize);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						window.close();
						break;
				}
			}

			gameContext.ProcessEvent(event);
		}
		
		gameContext.Update();
		gameContext.Draw(window);
		window.display();

		gameContext.SetSleep();
	}

	return 0;
}

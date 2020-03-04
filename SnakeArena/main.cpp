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
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				// Keys
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						window.close();
						break;
				}
			}
			else if (event.type == sf::Event::Resized) // Resize window
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
				gameContext.Resize({ event.size.width, event.size.height });
			}

			gameContext.ProcessEvent(event);
		}
		
		gameContext.Update();
		gameContext.Draw(window);

		gameContext.SetSleep();
	}

	return 0;
}

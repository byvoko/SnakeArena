#include "Menu.hpp"

Menu::Menu()
{

}

void Menu::Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha)
{
	if (mState == State::Exit || mState == State::Pause)
	{
		sf::RectangleShape bg(static_cast<sf::Vector2f>(window.getSize()));
		bg.setFillColor(sf::Color(0, 0, 0, 180));
		window.draw(bg);
	}

	switch (mState)
	{
		case State::None:
			break;
		case State::Exit:
			break;
		case State::Pause:
			break;
	}
}
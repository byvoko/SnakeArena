#include "Menu.hpp"

Menu::Menu() :
	mState(State::TopLevel),
	mSelectedItemIdx (0)
{
	mFont.loadFromFile(Font);
}

void Menu::Update()
{

}

void Menu::DrawTopLevel(sf::RenderWindow& window, sf::Transform t, uint8_t alpha = 255)
{
	const sf::Vector2u wSize = window.getSize();
	sf::Text text;
	sf::String s = "New Game";
	text.setString(s);
	text.setFont(mFont);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Magenta);
	text.setPosition({wSize.x * 0.2, wSize.y * 0.5});
	window.draw(text);

}

void Menu::DrawNewGame(sf::RenderWindow& window, sf::Transform t, uint8_t alpha = 255)
{

}

void Menu::Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha)
{
	window.clear();
	//TODO background

	switch (mState)
	{
		case State::TopLevel:
			DrawTopLevel(window, t, alpha);
			break;
		case State::NewGame:
			DrawNewGame(window, t, alpha);
			break;
	}

}

void Menu::ProcessEvent(sf::Event e)
{
	mControls.ProcessEvent(e);
}
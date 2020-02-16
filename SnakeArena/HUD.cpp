#include <string>

#include "HUD.hpp"
#include "Game.hpp" 

HUD::HUD()
{
	mFont.loadFromFile(Game::GameFont);
}

void HUD::Update()
{
}

void HUD::AddSnake(Snake & s) 
{ 
	mSnakes.push_back(&s); 
}

void HUD::Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha)
{
	//Background
	sf::Vector2f hudSize(window.getSize().x, Height);
	sf::RectangleShape background(hudSize);
	background.setFillColor(sf::Color(0, 0, 0));
	t.translate(0, (window.getSize().y - Height));
	window.draw(background, t);

	//Snakes
	t.translate(10, 10);
	for (Snake * snake : mSnakes)
	{
		if (snake == nullptr)
			continue;

		Snake & s = *snake;
		DrawSnakeInfo(window, t, s);
		t.translate(610, 0);
	}
}

void HUD::DrawSnakeInfo(sf::RenderWindow & window, sf::Transform t, Snake & s)
{
	const size_t snakeLength = s.GetLength();
	const uint8_t stamina = s.GetStamina();
	Color c = s.GetColor();

	std::string sLength = "Length: " + std::to_string(snakeLength) + " Stamina: " + std::to_string(stamina);
	sf::Text tLength;
	tLength.setString(sLength);
	tLength.setFont(mFont);
	tLength.setCharacterSize(30);
	tLength.setFillColor(c);
	
	window.draw(tLength, t);
}
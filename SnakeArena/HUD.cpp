#include <string>

#include <iostream>
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
	std::cout << "add snake " << mSnakes.size() << std::endl;
}

void HUD::Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha)
{
	//Background
	sf::Vector2f hudSize(window.getSize().x, Height);
	sf::RectangleShape background(hudSize);
	background.setFillColor(sf::Color(0, 0, 0));
	t.translate(0, (window.getSize().y - Height));
	window.draw(background, t);

	//std::cout << "Hadu " << mSnakes.size() << std::endl;
	//Snakes
	for (Snake * snake : mSnakes)
	{
		std::cout << "snake";
		Snake & s = *snake;
		DrawSnakeInfo(window, t, s);
		t.translate(100, 0);
	}
}

void HUD::DrawSnakeInfo(sf::RenderWindow & window, sf::Transform t, Snake & s)
{
	const size_t snakeLength = s.GetLength();
	const uint8_t stamina = s.GetStamina();
	Color c = s.GetColor();

	std::string sLength = "Length: " + snakeLength;
	sf::Text tLength;
	tLength.setString(sLength);
	tLength.setFont(mFont);
	tLength.setCharacterSize(50);
	tLength.setFillColor(c);
	
	window.draw(tLength, t);
}
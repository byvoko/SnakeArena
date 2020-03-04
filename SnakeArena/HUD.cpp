#include <string>

#include "HUD.hpp"
#include "Game.hpp" 

HUD::HUD()
{
	mFont.loadFromFile(Game::GameFont);
	mBackgroundColor = sf::Color(0x19, 0x08, 0x03);
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
	background.setFillColor(mBackgroundColor);
	t.translate(0, (window.getSize().y - Height));
	window.draw(background, t);

	const uint32_t InfoShift = mSnakes.size() > 2 ? 310 : 610;
	//Snakes
	t.translate(10, 10);
	for (Snake* snake : mSnakes)
	{
		if (snake == nullptr)
			continue;

		DrawSnakeInfo(window, t, *snake);
		t.translate(InfoShift, 0);
	}
}

void HUD::DrawSnakeInfo(sf::RenderWindow & window, sf::Transform t, Snake & s)
{
	const size_t snakeLength = s.GetLength();
	const uint8_t stamina = s.GetStamina();
	Color c = s.GetColor();

	std::string sLength = "Length: " + std::to_string(snakeLength);
	sf::Text tLength;
	tLength.setString(sLength);
	tLength.setFont(mFont);
	tLength.setCharacterSize(30);
	tLength.setFillColor(c);
	
	window.draw(tLength, t);
	t.translate(0, 45);

	//Stamina
	sf::Vector2f staminaSize = { 150, 30 };
	sf::RectangleShape rsStamina(staminaSize);
	rsStamina.setFillColor(mBackgroundColor);
	rsStamina.setOutlineColor(c);
	rsStamina.setOutlineThickness(1);
	window.draw(rsStamina, t);
	
	t.translate(2, 2);
	staminaSize.x = (staminaSize.x - 4) * ((float)stamina / Snake::MaxStamina);
	staminaSize.y -= 4;
	rsStamina.setSize(staminaSize);
	rsStamina.setOutlineThickness(0);
	rsStamina.setFillColor(c);
	window.draw(rsStamina, t);
}

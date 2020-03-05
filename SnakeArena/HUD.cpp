#include "HUD.hpp"

#include <string>

#include "Game.hpp"

HUD::HUD(sf::Vector2f hudSize)
	: mSnake(nullptr)
{
	mFont.loadFromFile(Game::GameFont);
	mHudRectangle.setFillColor(sf::Color(0x19, 0x08, 0x03));
	SetHudSize(hudSize);
}

void HUD::SetHudSize(sf::Vector2f hudSize)
{
	mHudSize = hudSize;
	mHudRectangle = sf::RectangleShape(hudSize);
}

void HUD::Update()
{
}

void HUD::AddSnake(Snake* s) 
{ 
	mSnake = s;
}

void HUD::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	if (mSnake == nullptr)
		return;

	window.draw(mHudRectangle, t);

	DrawSnakeInfo(window, t, mSnake);
}

void HUD::DrawSnakeInfo(sf::RenderWindow& window, sf::Transform t, Snake* s)
{
	const size_t snakeLength = s->GetLength();
	const uint8_t stamina = s->GetStamina();
	Color c = s->GetColor();

	// Text
	std::string sLength = "Length: " + std::to_string(snakeLength);
	sf::Text tLength;
	tLength.setString(sLength);
	tLength.setFont(mFont);
	tLength.setCharacterSize(mHudSize.y * 0.85f);
	tLength.setFillColor(c);
	
	window.draw(tLength, t);

	// Stamina
	t.translate(mHudSize.x * 0.375f, 4);

	sf::Vector2f staminaSize = { mHudSize.x * 0.25f, mHudSize.y * 0.80f };
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

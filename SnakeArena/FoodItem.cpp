#include "FoodItem.hpp"

FoodItem::FoodItem(Position position, sf::Vector2f tileSize)
	: BaseItem(position)
	, mShape(position, tileSize)
{
}

void FoodItem::Eat(Snake& snake)
{
	snake.IncrementLength();
	snake.RestoreStamina(4);
}

void FoodItem::Update()
{
}

void FoodItem::SetTileSize(sf::Vector2f tileSize)
{
	mShape = FoodItem::FoodItemShape(mPosition, tileSize);
}

void FoodItem::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	mShape.Draw(window, t, alpha);
}

// FoodItemShape

FoodItem::FoodItemShape::FoodItemShape(Position position, sf::Vector2f tileSize)
{
	const float scale = 0.7;
	body.setSize({ tileSize.x * scale, tileSize.y * scale });
	body.setPosition((position.x * tileSize.x) + ((tileSize.x - (tileSize.x * scale)) / 2.0), (position.y * tileSize.y) + (tileSize.y - (tileSize.y * scale)));
	body.setFillColor(sf::Color(0x8C, 0x23, 0x23));

	sf::Vector2f brownPartSize = { tileSize.x * 0.1f, tileSize.y * 0.3f };
	brownPart.setSize(brownPartSize);
	brownPart.setPosition((position.x * tileSize.x) + (tileSize.x / 2.0) - (brownPartSize.x / 2.0), (position.y * tileSize.y) + ((tileSize.y - (tileSize.y * scale)) / 2.0));
	brownPart.setFillColor(sf::Color(0xA6, 0x89, 0x32));

	sf::Vector2f greenPartSize = { tileSize.x * 0.4f, tileSize.y * 0.2f };
	greenPart.setSize(greenPartSize);
	greenPart.setPosition((position.x * tileSize.x) + (tileSize.x / 2.0), (position.y * tileSize.y) + ((tileSize.y - (tileSize.y * scale)) / 2.0));
	greenPart.setFillColor(sf::Color(0xAE, 0xBF, 0x2A));

	sf::Vector2f blackPartSize = { tileSize.x * 0.2f, tileSize.y * 0.1f };
	blackPart.setSize(blackPartSize);
	blackPart.setPosition((position.x * tileSize.x) + (tileSize.x / 2.0) - (blackPartSize.x / 2), (position.y * tileSize.y) + (tileSize.y - blackPartSize.y));
	blackPart.setFillColor(sf::Color(0x0, 0x0, 0x0));
}

void FoodItem::FoodItemShape::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	window.draw(body, t);
	window.draw(brownPart, t);
	window.draw(greenPart, t);
	window.draw(blackPart, t);
}

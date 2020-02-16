#include "FoodItem.hpp"

FoodItem::FoodItem(Position position, sf::Vector2f tileSize)
	: BaseItem(position)
{
	float removeX = (tileSize.x / 10.f);
	float removeY = (tileSize.y / 10.f);

	mShape.setSize({ tileSize.x - removeX, tileSize.y - removeY });
	mShape.setPosition((position.x * tileSize.x) + (removeX / 2), (position.y * tileSize.y) + (removeY / 2));
	mShape.setFillColor(sf::Color(0x8C, 0x23, 0x23));
}

void FoodItem::Eat(Snake& snake)
{
	snake.IncrementLength();
	snake.RestoreStamina(4);
}

void FoodItem::Update()
{
}

void FoodItem::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	window.draw(mShape, t);
}

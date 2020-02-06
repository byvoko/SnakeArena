#include "FoodItem.hpp"

FoodItem::FoodItem(Position position, sf::Vector2u tileSize)
	: BaseItem(position)
	, mHorizontalPlusLine(sf::Vector2f(tileSize.x, tileSize.y / 3.f))
	, mVerticalPlusLine(sf::Vector2f(tileSize.x / 3.f, tileSize.y))
{
	mHorizontalPlusLine.setPosition(position.x * tileSize.x, position.y * tileSize.y + tileSize.y / 3.f);
	mVerticalPlusLine.setPosition(position.x * tileSize.x + tileSize.x / 3.f, position.y * tileSize.y);

	mHorizontalPlusLine.setFillColor(Color(255, 10, 10));
	mVerticalPlusLine.setFillColor(Color(255, 10, 10));
}

void FoodItem::Eat(Snake & snake)
{
	snake.IncrementLength();
}

void FoodItem::Update()
{
}

void FoodItem::Draw(sf::RenderWindow& window, sf::Transform t)
{
	window.draw(mHorizontalPlusLine, t);
	window.draw(mVerticalPlusLine, t);
}

#include "FoodItem.hpp"

FoodItem::FoodItem(Position position, sf::Vector2f tileSize)
	: BaseItem(position)
	, mHorizontalPlusLine(sf::Vector2f(tileSize.x, tileSize.y / 3.f))
	, mVerticalPlusLine(sf::Vector2f(tileSize.x / 3.f, tileSize.y))
{
	mHorizontalPlusLine.setPosition(position.x, position.y + tileSize.y / 3.f);
	mVerticalPlusLine.setPosition(position.x + tileSize.x / 3.f, position.y);

	mHorizontalPlusLine.setFillColor(Color(255, 10, 10));
	mVerticalPlusLine.setFillColor(Color(255, 10, 10));
}

void FoodItem::Eat(Snake & snake)
{
	snake.IncrementLength();
}

void FoodItem::Draw(sf::RenderWindow & window, sf::Vector2u offsetPosition)
{
	auto positionH = mHorizontalPlusLine.getPosition();
	auto positionV = mVerticalPlusLine.getPosition();

	positionH.x += offsetPosition.x;
	positionH.y += offsetPosition.y;

	positionV.x += offsetPosition.x;
	positionV.y += offsetPosition.y;

	mHorizontalPlusLine.setPosition(positionH);
	mVerticalPlusLine.setPosition(positionV);

	window.draw(mHorizontalPlusLine);
	window.draw(mVerticalPlusLine);
}

void FoodItem::Update()
{
}

#pragma once

#include "BaseItem.hpp"

class FoodItem :
	public BaseItem
{
private:
	sf::RectangleShape mHorizontalPlusLine;
	sf::RectangleShape mVerticalPlusLine;

public:
	FoodItem(Position position, sf::Vector2f tileSize);

	// Dìdí se pøes BaseItem.
	virtual void Eat(Snake & snake) override;
	virtual void Draw(sf::RenderWindow & window, sf::Vector2u offsetPosition) override;
	virtual void Update() override;
};


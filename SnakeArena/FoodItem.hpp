#pragma once

#include "BaseItem.hpp"

class FoodItem :
	public BaseItem
{
private:
	sf::RectangleShape mShape;

public:
	FoodItem(Position position, sf::Vector2f tileSize);

	// D�d� se p�es BaseItem.
	virtual void Eat(Snake & snake) override;

	virtual void Update() override;

	// D�d� se p�es BaseItem.
	virtual void Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha = 255) override;
};

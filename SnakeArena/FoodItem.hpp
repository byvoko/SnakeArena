#pragma once

#include "BaseItem.hpp"
#include "Types.hpp"
#include <SFML/Graphics.hpp>

class FoodItem : public BaseItem
{
public:
	class FoodItemShape : public IGameDrawable
	{
	private:
		sf::RectangleShape body;
		sf::RectangleShape brownPart;
		sf::RectangleShape greenPart;
		sf::RectangleShape blackPart;

	public:
		FoodItemShape(Position position, sf::Vector2f tileSize);

		void Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha = 255) override;
	};

private:
	FoodItemShape mShape;

public:
	FoodItem(Position position, sf::Vector2f tileSize);

	// Dìdí se pøes BaseItem.
	virtual void Eat(Snake & snake) override;

	virtual void Update() override;

	virtual void SetTileSize(sf::Vector2f tileSize);

	// Dìdí se pøes BaseItem.
	virtual void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;
};

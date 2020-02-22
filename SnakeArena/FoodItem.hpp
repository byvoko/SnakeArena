#pragma once

#include "BaseItem.hpp"
#include "Types.hpp"
#include <SFML/Graphics.hpp>

class FoodItem :
	public BaseItem
{
public:
	class FoodItemShape : public IGameDrawable
	{
	public:
		FoodItemShape(Position position, sf::Vector2f tileSize);

		void Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha = 255) override;
	private:
		sf::RectangleShape body;
		sf::RectangleShape brownPart;
		sf::RectangleShape greenPart;
		sf::RectangleShape blackPart;
	};

private:
	FoodItemShape mShape;
	

public:
	FoodItem(Position position, sf::Vector2f tileSize);

	// D�d� se p�es BaseItem.
	virtual void Eat(Snake & snake) override;

	virtual void Update() override;

	// D�d� se p�es BaseItem.
	virtual void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;
};

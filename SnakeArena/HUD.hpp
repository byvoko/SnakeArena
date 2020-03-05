#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

#include "Snake.hpp"
#include "IGameDrawable.hpp"

class HUD : public IGameDrawable
{
private:
	sf::Vector2f mHudSize;
	sf::RectangleShape mHudRectangle;

	sf::Color mBackgroundColor;
	sf::Font mFont;
	Snake* mSnake;

	void DrawSnakeInfo(sf::RenderWindow& window, sf::Transform t, Snake* s);

public:
	HUD(sf::Vector2f hudSize);

	void SetHudSize(sf::Vector2f hudSize);

	void AddSnake(Snake* s);
	void Update();
	void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;
};

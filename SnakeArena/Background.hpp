#pragma once

#include <SFML\Graphics.hpp>

#include "IGameDrawable.hpp"

class Background : public IGameDrawable
{
protected:
	sf::RectangleShape mRectangle;

public:
	Background(const sf::Vector2u& sizePx);

	void Update();

	// Dìdí se pøes IGameDrawable.
	virtual void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;
};


#pragma once

#include <SFML\Graphics.hpp>

class IGameDrawable
{
public:
	virtual void Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha = 255) = 0;
};

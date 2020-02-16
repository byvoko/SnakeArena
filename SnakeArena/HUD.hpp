#pragma once

#include <SFML\Graphics.hpp>
#include "IGameDrawable.hpp"

class HUD : public IGameDrawable
{
public:
	static constexpr size_t Height = 100;	//[px]
	void Update();
	void Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha = 255);
};

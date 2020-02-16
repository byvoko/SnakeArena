#pragma once

#include <SFML\Graphics.hpp>
#include "Snake.hpp"
#include "IGameDrawable.hpp"

class HUD : public IGameDrawable
{
private:
	sf::Font mFont;
	std::vector<Snake*> mSnakes;

	void DrawSnakeInfo(sf::RenderWindow & window, sf::Transform t, Snake & s);
public:

	HUD();
	void AddSnake(Snake & s);
	static constexpr size_t Height = 100;	//[px]
	void Update();
	void Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha = 255);
};

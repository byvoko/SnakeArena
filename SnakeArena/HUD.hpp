#pragma once

#include <vector>

#include <SFML\Graphics.hpp>
#include "Snake.hpp"
#include "IGameDrawable.hpp"

class HUD : public IGameDrawable
{
private:
	sf::Color mBackgroundColor;
	sf::Font mFont;
	std::vector<Snake*> mSnakes;

	void DrawSnakeInfo(sf::RenderWindow & window, sf::Transform t, Snake & s);

public:
	static constexpr size_t Height = 100;	//[px]

	HUD();

	void AddSnake(Snake & s);
	void Update();
	void Draw(sf::RenderWindow & window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;
};

#pragma once

#include <SFML\Graphics.hpp>

#include "Snake.hpp"

class Arena
{
private:
	std::vector<Snake*> mSnakes;

	sf::Vector2u mSizePx;
	sf::Vector2u mGridTileSize;
	sf::Vector2u mPosition;

public:
	Arena(sf::Vector2u sizePx, sf::Vector2u gridTileSize, sf::Vector2u position);
	virtual ~Arena();

	void Draw(sf::RenderWindow & window);
	void Update();

	sf::Vector2f CalcTileSize();
	sf::Vector2u GetGridTileSize() { return mGridTileSize; }

	void AddSnake(Snake & snake) { mSnakes.push_back(&snake); }
};

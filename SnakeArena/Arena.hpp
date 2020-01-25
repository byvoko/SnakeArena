#pragma once

#include <SFML\Graphics.hpp>

#include "Snake.hpp"

class Arena
{
private:
	std::vector<Snake&> mSnakes;

	sf::Vector2u mSizePx;
	sf::Vector2u mGridTileSize;

public:
	Arena(sf::Vector2u sizePx, sf::Vector2u gridTileSize);
	virtual ~Arena();

	void Draw(sf::Window window);
	void Update();
};

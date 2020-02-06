#pragma once

#include <SFML\Graphics.hpp>

#include "Snake.hpp"
#include "BaseItem.hpp"

class Arena
{
private:
	std::vector<Snake*> mSnakes;
	std::vector<BaseItem*>& pItems;

	sf::Vector2u mSizePx;
	sf::Vector2u mGridTileSize;

	sf::Transform mTransform;

public:
	Arena(sf::Vector2u sizePx, sf::Vector2u gridTileSize, sf::Vector2u position, std::vector<BaseItem*>& items);
	virtual ~Arena();

	void Draw(sf::RenderWindow & window);
	void Update();

	sf::Vector2f CalcTileSize();
	sf::Vector2u GetGridTileSize() { return mGridTileSize; }

	void AddSnake(Snake & snake) { mSnakes.push_back(&snake); }
};

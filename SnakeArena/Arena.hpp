#pragma once

#include <SFML\Graphics.hpp>

#include "Snake.hpp"
#include "BaseItem.hpp"
#include "FoodItem.hpp"

class Arena
{
private:
	std::vector<Snake*> mSnakes;
	std::vector<Snake*> mShadows;
	FoodItem* pFood;

	sf::Vector2u mSizePx;
	sf::Vector2u mGridTileSize;

	sf::Transform mTransform;

public:
	Arena(sf::Vector2u sizePx, sf::Vector2u gridTileSize, sf::Vector2u position, FoodItem* foodItem = nullptr);
	virtual ~Arena();

	void Draw(sf::RenderWindow & window);
	void Update(const uint64_t& mUpdateId);

	sf::Vector2f CalcTileSize();
	sf::Vector2u GetGridTileSize() { return mGridTileSize; }

	void AddSnake(Snake & snake) { mSnakes.push_back(&snake); }
	void AddShadow(Snake& shadow) { mShadows.push_back(&shadow); }
	void AddFood(FoodItem* food);
};

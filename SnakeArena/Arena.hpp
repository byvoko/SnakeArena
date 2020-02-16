#pragma once

#include <SFML\Graphics.hpp>

#include "Snake.hpp"
#include "EatEffect.hpp"
#include "BaseItem.hpp"
#include "FoodItem.hpp"

class Arena
{
private:
	std::vector<Snake*> mSnakes;
	std::vector<Snake*> mShadows;
	FoodItem* pFood;
	EatEffect** ppEatEffect;

	sf::Vector2u mSizePx;
	sf::Vector2f mGridTileSize;

	sf::Transform mTransform;

public:
	Arena(sf::Vector2u sizePx, sf::Vector2f gridTileSize, sf::Vector2u position, EatEffect** eatEffect, FoodItem* foodItem = nullptr);
	virtual ~Arena();

	void Draw(sf::RenderWindow & window);
	void Update(const uint64_t& mUpdateId);

	sf::Vector2u GetGridResolution();
	sf::Vector2f GetGridTileSize() { return mGridTileSize; }

	void AddSnake(Snake & snake) { mSnakes.push_back(&snake); }
	void AddShadow(Snake& shadow) { mShadows.push_back(&shadow); }
	void AddFood(FoodItem* food);
	void AddEffect(EatEffect** eatEffect) { ppEatEffect = eatEffect; }
};

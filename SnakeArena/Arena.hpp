#pragma once

#include <SFML\Graphics.hpp>

#include "Snake.hpp"
#include "EatEffect.hpp"
#include "BaseItem.hpp"
#include "FoodItem.hpp"
#include "Background.hpp"
#include "HUD.hpp"

class Arena
{
private:
	std::vector<Snake*> mSnakes;
	std::vector<Snake*> mShadows;
	FoodItem* pFood;
	HUD mHud;
	Background mBackground;

	sf::Vector2u mSizePx;
	sf::Vector2f mGridTileSize;

	sf::Transform mTransform;

public:
	Arena(sf::Vector2u arenaSizePx, sf::Vector2f gridTileSize, sf::Vector2u position);
	virtual ~Arena();

	void Draw(sf::RenderWindow & window);
	void Update(const uint64_t& mUpdateId);

	sf::Vector2u GetGridResolution();
	sf::Vector2f GetGridTileSize() { return mGridTileSize; }

	void AddSnake(Snake* snake);
	void AddShadow(Snake* shadow);
	void AddFood(FoodItem* food);

	// Setters sf::Vector2u sizePx, sf::Vector2f gridTileSize, sf::Vector2u position
	void SetSize(sf::Vector2u arenaSizePx, sf::Vector2f gridTileSize);
	void SetPosition(sf::Vector2u position);
};

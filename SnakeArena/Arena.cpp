#include "Arena.hpp"
#include "Snake.hpp"

Arena::Arena(sf::Vector2u sizePx, sf::Vector2f gridTileSize, sf::Vector2u position, EatEffect** eatEffect, FoodItem* foodItem) :
	mSizePx(sizePx),
	mGridTileSize(gridTileSize),
	pFood(foodItem),
	ppEatEffect(eatEffect)
{
	mTransform.translate(static_cast<sf::Vector2f>(position));
}

Arena::~Arena()
{
}

void Arena::Draw(sf::RenderWindow & window)
{
	if (mSnakes.size() == 0)
		return;

	for (auto pShadow : mShadows)
	{
		if (pShadow == nullptr)
			continue;

		pShadow->Draw(window, mTransform, 65);
	}

	for (auto pSnake : mSnakes)
	{
		if (pSnake == nullptr)
			continue;

		pSnake->Draw(window, mTransform);
	}
	
	if (pFood)
		pFood->Draw(window, mTransform);
	if (*ppEatEffect)
		(*ppEatEffect)->Draw(window, mTransform);

	sf::RectangleShape bondries(sf::Vector2f(mSizePx.x, mSizePx.y));
	bondries.setPosition(0, 0);
	bondries.setOutlineThickness(3.f);
	bondries.setOutlineColor(sf::Color(0, 0, 0));
	bondries.setFillColor(sf::Color(0, 0, 0, 0));

	// Draw arena boundries
	window.draw(bondries, mTransform);
}

void Arena::Update(const uint64_t& mUpdateId)
{
	if (mSnakes.size() == 0)
		return;

	for (auto pSnake : mSnakes)
	{
		if (pSnake == nullptr)
			continue;

		pSnake->Update(mUpdateId);
	}
}

sf::Vector2u Arena::GetGridResolution()
{
	return sf::Vector2u { unsigned int(mSizePx.x / mGridTileSize.x), unsigned int(mSizePx.y / mGridTileSize.y)};
}

void Arena::AddFood(FoodItem* food)
{
	pFood = food;
}

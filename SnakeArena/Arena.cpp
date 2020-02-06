#include "Arena.hpp"
#include "Snake.hpp"

Arena::Arena(sf::Vector2u sizePx, sf::Vector2u gridTileSize, sf::Vector2u position, std::vector<BaseItem*>& items) :
	mSizePx(sizePx),
	mGridTileSize(gridTileSize),
	pItems(items)
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

	for (auto pSnake : mSnakes)
	{
		if (pSnake == nullptr)
			continue;

		Snake & snake = *pSnake;
		snake.Draw(window, mTransform);
	}

	for (BaseItem* baseItem : pItems)
	{
		baseItem->Draw(window, mTransform);
	}

	sf::RectangleShape bondries(sf::Vector2f(mSizePx.x, mSizePx.y));
	bondries.setPosition(0, 0);
	bondries.setOutlineThickness(3.f);
	bondries.setOutlineColor(sf::Color(0, 0, 0));
	bondries.setFillColor(sf::Color(0, 0, 0, 0));

	// Draw arena boundries
	window.draw(bondries, mTransform);
}

void Arena::Update()
{
	if (mSnakes.size() == 0)
		return;

	for (auto pSnake : mSnakes)
	{
		if (pSnake == nullptr)
			continue;

		pSnake->Update();
	}
}

sf::Vector2f Arena::CalcTileSize()
{
	return sf::Vector2f { float(mSizePx.x / mGridTileSize.x), float(mSizePx.y / mGridTileSize.y)};
}



#include "Arena.hpp"
#include "Snake.hpp"

Arena::Arena(sf::Vector2u sizePx, sf::Vector2u gridTileSize):
	mSizePx (sizePx),
	mGridTileSize (gridTileSize)
{

}

Arena::~Arena()
{
}

void Arena::Draw(sf::RenderWindow & window)
{
	auto tileSize = CalcTileSize();
	sf::RectangleShape bodyShape(tileSize);
	bodyShape.setOutlineThickness(1.f);
	bodyShape.setOutlineColor(sf::Color(250, 150, 100));

	if (mSnakes.size() == 0)
		return;

	for (auto pSnake : mSnakes)
	{
		if (pSnake == nullptr)
			continue;

		Snake & snake = *pSnake;
		std::pair<Snake::Positions, Snake::Color> snakeBody = snake.GetBody();
		bodyShape.setFillColor(snakeBody.second);
		for (auto position : snakeBody.first)
		{
			bodyShape.setPosition(position.x * tileSize.x, position.y * tileSize.y);
			window.draw(bodyShape);
		}
	}
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
	return sf::Vector2f{ float(mSizePx.x / mGridTileSize.x), float(mSizePx.y / mGridTileSize.y)};
}



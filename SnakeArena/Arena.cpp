#include "Arena.hpp"
#include "Snake.hpp"

Arena::Arena(sf::Vector2u sizePx, sf::Vector2u gridTileSize):
	mSizePx (sizePx),
	mGridTileSize (gridTileSize)
{

}

void Arena::Draw(sf::RenderWindow & window)
{
	auto tileSize = CalcTileSize();
	sf::RectangleShape bodyShape(tileSize);

	for (auto snake : mSnakes)
	{
		std::pair<Snake::Position, Snake::Color> snakeBody = snake.GetBody();
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
	for (auto snake : mSnakes)
	{
		snake.Update();
	}
}

sf::Vector2f Arena::CalcTileSize()
{
	return { mSizePx.x / mGridTileSize.x, mSizePx.y / mGridTileSize.y};
}



#include "Arena.hpp"
#include "Snake.hpp"

Arena::Arena(sf::Vector2u sizePx, sf::Vector2u gridTileSize, sf::Vector2u position) :
	mSizePx(sizePx),
	mGridTileSize(gridTileSize),
	mBondries(sf::Vector2f(sizePx.x, sizePx.y))
{
	mBondries.setPosition(position.x, position.y);
	mBondries.setOutlineThickness(3.f);
	mBondries.setOutlineColor(sf::Color(0, 0, 0));
	mBondries.setFillColor(sf::Color(0, 0, 0, 0));
}

Arena::~Arena()
{
}

void Arena::Draw(sf::RenderWindow & window)
{
	auto tileSize = CalcTileSize();
	sf::RectangleShape bodyShape(tileSize);

	if (mSnakes.size() == 0)
		return;

	for (auto pSnake : mSnakes)
	{
		if (pSnake == nullptr)
			continue;

		Snake & snake = *pSnake;
		Positions snakeBody = snake.GetBody();

		// Draw head
		bodyShape.setFillColor(snake.GetHeadColor());
		bodyShape.setPosition(snakeBody[0].x * tileSize.x, snakeBody[0].y * tileSize.y);
		window.draw(bodyShape);

		// Draw body
		bodyShape.setFillColor(snake.GetColor());
		for (size_t i = 1; i < snakeBody.size(); i++)
		{
			bodyShape.setPosition(snakeBody[i].x * tileSize.x, snakeBody[i].y * tileSize.y);
			window.draw(bodyShape);
		}
	}

	// Draw arena boundries
	window.draw(mBondries);
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



#include "Arena.hpp"
#include "Snake.hpp"

Arena::Arena(sf::Vector2u sizePx, sf::Vector2u gridTileSize, sf::Vector2u position) :
	mSizePx(sizePx),
	mGridTileSize(gridTileSize),
	mPosition (position)
{

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
		Snake::Positions snakeBody = snake.GetBody();

		// Draw head
		bodyShape.setFillColor(snake.GetHeadColor());
		bodyShape.setPosition(mPosition.x + (snakeBody[0].x * tileSize.x), mPosition.y + (snakeBody[0].y * tileSize.y));
		window.draw(bodyShape);

		// Draw body
		bodyShape.setFillColor(snake.GetColor());
		for (size_t i = 1; i < snakeBody.size(); i++)
		{
			bodyShape.setPosition(mPosition.x + (snakeBody[i].x * tileSize.x), mPosition.y + (snakeBody[i].y * tileSize.y));
			window.draw(bodyShape);
		}
	}

	sf::RectangleShape bondries(sf::Vector2f(mSizePx.x, mSizePx.y));
	bondries.setPosition(mPosition.x, mPosition.y);
	bondries.setOutlineThickness(3.f);
	bondries.setOutlineColor(sf::Color(0, 0, 0));
	bondries.setFillColor(sf::Color(0, 0, 0, 0));

	// Draw arena boundries
	window.draw(bondries);
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



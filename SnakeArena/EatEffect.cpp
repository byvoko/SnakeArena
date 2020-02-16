#include "EatEffect.hpp"

#include <iostream>

EatEffect::EatEffect(Position position, sf::Vector2f gridTileSize, Color color, Snake::Direction direction, uint64_t lifeTime)
	: mLifeTimePassed(0)
	, mLifeTime(lifeTime)
	, mDirection(direction)
{
	if (mDirection == Snake::Direction::Up || mDirection == Snake::Direction::Down)
	{
		sf::Vector2f rectangleSize = sf::Vector2f(gridTileSize.x, gridTileSize.y / 6);

		// Left
		mRectangles[0] = sf::RectangleShape(rectangleSize);
		mRectangles[0].setPosition(position.x * gridTileSize.x - gridTileSize.x / 4, position.y * gridTileSize.y - gridTileSize.y * 3 / 4);
		mRectangles[1] = sf::RectangleShape(rectangleSize);
		mRectangles[1].setPosition(position.x * gridTileSize.x - gridTileSize.x / 4, position.y * gridTileSize.y - gridTileSize.y * 2 / 4);
		mRectangles[2] = sf::RectangleShape(rectangleSize);
		mRectangles[2].setPosition(position.x * gridTileSize.x - gridTileSize.x / 4, position.y * gridTileSize.y - gridTileSize.y * 1 / 4);

		// Right
		mRectangles[3] = sf::RectangleShape(rectangleSize);
		mRectangles[3].setPosition(position.x * gridTileSize.x + gridTileSize.x / 4, position.y * gridTileSize.y - gridTileSize.y * 3 / 4);
		mRectangles[4] = sf::RectangleShape(rectangleSize);
		mRectangles[4].setPosition(position.x * gridTileSize.x + gridTileSize.x / 4, position.y * gridTileSize.y - gridTileSize.y * 2 / 4);
		mRectangles[5] = sf::RectangleShape(rectangleSize);
		mRectangles[5].setPosition(position.x * gridTileSize.x + gridTileSize.x / 4, position.y * gridTileSize.y - gridTileSize.y * 1 / 4);

	}
	else
	{
		sf::Vector2f rectangleSize = sf::Vector2f(gridTileSize.x / 6, gridTileSize.y);

		// Top
		mRectangles[0] = sf::RectangleShape(rectangleSize);
		mRectangles[0].setPosition(position.x * gridTileSize.x + gridTileSize.x * 1 / 4, position.y * gridTileSize.y - gridTileSize.y / 4);
		mRectangles[1] = sf::RectangleShape(rectangleSize);
		mRectangles[1].setPosition(position.x * gridTileSize.x + gridTileSize.x * 2 / 4, position.y * gridTileSize.y - gridTileSize.y / 4);
		mRectangles[2] = sf::RectangleShape(rectangleSize);
		mRectangles[2].setPosition(position.x * gridTileSize.x + gridTileSize.x * 3/ 4, position.y * gridTileSize.y - gridTileSize.y / 4);

		// Bot
		mRectangles[3] = sf::RectangleShape(rectangleSize);
		mRectangles[3].setPosition(position.x * gridTileSize.x + gridTileSize.x * 1 / 4, position.y * gridTileSize.y + gridTileSize.y / 4);
		mRectangles[4] = sf::RectangleShape(rectangleSize);
		mRectangles[4].setPosition(position.x * gridTileSize.x + gridTileSize.x * 2 / 4, position.y * gridTileSize.y + gridTileSize.y / 4);
		mRectangles[5] = sf::RectangleShape(rectangleSize);
		mRectangles[5].setPosition(position.x * gridTileSize.x + gridTileSize.x * 3 / 4, position.y * gridTileSize.y + gridTileSize.y / 4);
	}

	for (auto& rec : mRectangles)
	{
		rec.setFillColor(color);
	}
}

EatEffect::~EatEffect()
{
}

bool EatEffect::HasLifetimeEnded() const
{
	std::cout << mLifeTimePassed << std::endl;
	return mLifeTimePassed > mLifeTime;
}

void EatEffect::Update()
{
	mLifeTimePassed++;

	sf::Vector2f pos;
	if (mDirection == Snake::Direction::Up || mDirection == Snake::Direction::Down)
	{
		for (int i = 0; i < 6; i++)
		{
			pos = mRectangles[i].getPosition();
			mRectangles[i].setPosition(pos.x + (i < 3 ? - 1 : 1), pos.y);
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			pos = mRectangles[i].getPosition();
			mRectangles[i].setPosition(pos.x, pos.y + (i < 3 ? -1 : 1));
		}
	}
}

void EatEffect::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	for (auto& rec : mRectangles)
	{
		window.draw(rec, t);
	}
}

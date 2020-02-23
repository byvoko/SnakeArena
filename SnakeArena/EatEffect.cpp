#include "EatEffect.hpp"

#include <iostream>

EatEffect::EatEffect(Position position, sf::Vector2f gridTileSize, Color color, Snake::Direction direction, uint64_t lifeTime)
	: mLifeTimePassed(0)
	, mLifeTime(lifeTime)
	, mDirection(direction)
{
	sf::Vector2f rectangleSize = sf::Vector2f(gridTileSize.x / 6, gridTileSize.y / 6);
	mRectangle = sf::RectangleShape(rectangleSize);
	mRectangle.setFillColor(color);
	mRectangle.setOrigin(rectangleSize.x / 2, rectangleSize.y / 2);

	mCenterPositionCalculated = Position(position.x * gridTileSize.x + gridTileSize.x / 2, position.y * gridTileSize.y + gridTileSize.y / 2);

	switch (mDirection)
	{
	case Snake::Direction::Up:
	case Snake::Direction::Down:
		mRectangle.setPosition(mCenterPositionCalculated.x - gridTileSize.x / 1.2f, mCenterPositionCalculated.y);
		break;
	case Snake::Direction::Right:
	case Snake::Direction::Left:
		mRectangle.setPosition(mCenterPositionCalculated.x, mCenterPositionCalculated.y - gridTileSize.y / 1.2f);
		break;
	}
}

EatEffect::~EatEffect()
{
}

bool EatEffect::HasLifetimeEnded() const
{
	return mLifeTimePassed > mLifeTime;
}

void EatEffect::Update()
{
	mLifeTimePassed++;

	sf::Vector2f pos = mRectangle.getPosition();

	switch (mDirection)
	{
	case Snake::Direction::Up:
	case Snake::Direction::Down:
		mRectangle.setPosition(pos.x - 1, pos.y);
		break;
	case Snake::Direction::Right:
	case Snake::Direction::Left:
		mRectangle.setPosition(pos.x, pos.y - 1);
		break;
	}
}

void EatEffect::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	for (int i = 0; i < 9; i++)
	{
		window.draw(mRectangle, t);
		switch (mDirection)
		{
		case Snake::Direction::Up:
		case Snake::Direction::Right:
			t.rotate(22.5f, mCenterPositionCalculated.x, mCenterPositionCalculated.y);
			break;
		case Snake::Direction::Down:
		case Snake::Direction::Left:
			t.rotate(-22.5f, mCenterPositionCalculated.x, mCenterPositionCalculated.y);
			break;
		}
	}
}

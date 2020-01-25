#include "Snake.hpp"

Snake::Snake(Color color, sf::Vector2u startPosition, size_t bodyLen):
	mColor (color),
	mDirection (Direction::Up),
	mBodyLen (bodyLen)
{
	mPositions.push_back(startPosition);
	for (size_t i = 0; i < bodyLen; i++)
	{
		mPositions.push_back({ startPosition.x, startPosition.y + 1 });
	}
}

Snake::~Snake()
{
}

void Snake::Update()
{
	switch (mDirection)
	{
	case Snake::Up:
		Move({ mPositions[0].x, mPositions[0].y - 1 });
		break;
	case Snake::Right:
		Move({ mPositions[0].x + 1, mPositions[0].y });
		break;
	case Snake::Down:
		Move({ mPositions[0].x, mPositions[0].y + 1 });
		break;
	case Snake::Left:
		Move({ mPositions[0].x - 1, mPositions[0].y });
		break;
	default:
		break;
	}
}

// Private methods

void Snake::Move(Position newHeadPosition)
{
	for (Positions::reverse_iterator it = mPositions.rbegin(); it != mPositions.rend() - 1; it++)
	{
		it->x = (it + 1)->x;
		it->y = (it + 1)->y;
	}

	mPositions[0] = newHeadPosition;
}

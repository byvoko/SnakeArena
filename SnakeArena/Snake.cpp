#include "Snake.hpp"

Snake::Snake(Color color, sf::Vector2u startPosition, size_t bodyLen):
	mColor (color),
	mDirection (Direction::Up),
	mBodyLen (bodyLen)
{
	for (int i = 0; i < bodyLen; i++)
	{
		mPositions.push_back({ startPosition.x, startPosition.y + i });
	}
}

Snake::~Snake()
{
}

void Snake::Update()
{
	ProcessDirectionChange();

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

void Snake::AddControl(ISnakeControls & c)
{
	mControl = &c;
	c.UpEvent = [&]{ this->ChangeDirection(Direction::Up); };
	c.RightEvent = [&]{ this->ChangeDirection(Direction::Right); };
	c.DownEvent = [&]{ this->ChangeDirection(Direction::Down); };
	c.LeftEvent = [&]{ this->ChangeDirection(Direction::Left); };
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

void Snake::ChangeDirection(Direction d)
{
	mTempDirection = d;
}

void Snake::ProcessDirectionChange()
{
	if (mTempDirection == Direction::Up && mDirection == Direction::Down)
		return;

	if (mTempDirection == Direction::Down && mDirection == Direction::Up)
		return;

	if (mTempDirection == Direction::Right && mDirection == Direction::Left)
		return;

	if (mTempDirection == Direction::Left && mDirection == Direction::Right)
		return;

	mDirection = mTempDirection;
}

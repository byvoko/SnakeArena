#include "Snake.hpp"

Snake::Snake(Color color, sf::Vector2u startPosition, sf::Vector2f tileSize, size_t bodyLen):
	mColor (color),
	mHeadColor (Color(color.r * 0.75f, color.g * 0.75f, color.b * 0.75f)),
	mDirection (Direction::Up),
	mTileSize (tileSize),
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

Position Snake::GetNext()
{
	switch (mDirection)
	{
	case Snake::Up:
		return { mPositions[0].x, mPositions[0].y - 1 };
		break;
	case Snake::Right:
		return { mPositions[0].x + 1, mPositions[0].y };
		break;
	case Snake::Down:
		return { mPositions[0].x, mPositions[0].y + 1 };
		break;
	case Snake::Left:
		return { mPositions[0].x - 1, mPositions[0].y };
		break;
	default:
		break;
	}
	return {};
}

void Snake::Update()
{
	ProcessDirectionChange();

	Move(GetNext());
}

void Snake::AddControl(ISnakeControls & c)
{
	mControl = &c;

	c.UpEvent = [&]{ this->ChangeDirection(Direction::Up); };
	c.RightEvent = [&]{ this->ChangeDirection(Direction::Right); };
	c.DownEvent = [&]{ this->ChangeDirection(Direction::Down); };
	c.LeftEvent = [&]{ this->ChangeDirection(Direction::Left); };
}

void Snake::IncrementLength()
{
	mBodyLen++;

	mPositions.push_back(Position(mPositions.back()));
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

void Snake::Draw(sf::RenderWindow & window, sf::Transform t)
{
	sf::RectangleShape bodyShape(mTileSize);

	Positions snakeBody = GetBody();

	// Draw head
	bodyShape.setFillColor(GetHeadColor());
	bodyShape.setPosition(snakeBody[0].x * mTileSize.x, snakeBody[0].y * mTileSize.y);
	window.draw(bodyShape, t);

	// Draw body
	bodyShape.setFillColor(GetColor());
	for (size_t i = 1; i < snakeBody.size(); i++)
	{
		bodyShape.setPosition(snakeBody[i].x * mTileSize.x, snakeBody[i].y * mTileSize.y);
		window.draw(bodyShape, t);
	}
}
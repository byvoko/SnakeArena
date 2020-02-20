#include "Snake.hpp"

const uint8_t Snake::MaxStamina = 20;

Snake::Snake(Color color, sf::Vector2u startPosition, sf::Vector2f tileSize, size_t bodyLen):
	mColor (color),
	mHeadColor (Color(color.r * 0.75f, color.g * 0.75f, color.b * 0.75f)),
	mDirection (Direction::Up),
	mTileSize (tileSize),
	mBodyLen (bodyLen),
	mNextUpdateId(0),
	mUpdateIdStep(10),
	mNitroEnable (false),
	mNitronYank (false),
	mStamina(Snake::MaxStamina)
{
	for (int i = 0; i < bodyLen; i++)
	{
		mPositions.push_back({ startPosition.x, startPosition.y });
	}
}

Snake::~Snake()
{
}

Position Snake::GetNext()
{
	ProcessDirectionChange();
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

uint8_t Snake::GetStamina()
{
	return mStamina;
}

bool Snake::ShouldUpdate(const uint64_t& updateId)
{
	return updateId >= mNextUpdateId;
}

void Snake::Update(const uint64_t& updateId)
{
	if (ShouldUpdate(updateId))
	{
		mNitronYank |= mNitroEnable;

		if (mNitronYank && mStamina > 0)
		{
			mNextUpdateId += mUpdateIdStep / 3;
			mStamina--;
		}
		else
		{
			mNextUpdateId += mUpdateIdStep;
		}

		mNitronYank = false;

		Move(GetNext());
	}
}

void Snake::AddControl(ISnakeControls & c)
{
	mControl = &c;

	c.UpEvent = [&]{ this->ChangeDirection(Direction::Up); };
	c.RightEvent = [&]{ this->ChangeDirection(Direction::Right); };
	c.DownEvent = [&]{ this->ChangeDirection(Direction::Down); };
	c.LeftEvent = [&]{ this->ChangeDirection(Direction::Left); };
	c.NitroEventPull = [&] { this->DisableNitro(); };
	c.NitroEventPush = [&] { this->EnableNitro(); };
}

void Snake::IncrementLength()
{
	mBodyLen++;

	mPositions.push_back(Position(mPositions.back()));
}

void Snake::RestoreStamina(uint8_t stamina)
{
	mStamina += stamina;
	if (mStamina > MaxStamina)
	{
		mStamina = MaxStamina;
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

void Snake::Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha)
{
	sf::RectangleShape bodyShape(mTileSize);

	Positions snakeBody = GetBody();

	// Draw head
	Color headColor = GetHeadColor();
	headColor.a = alpha;
	bodyShape.setFillColor(headColor);
	bodyShape.setPosition(snakeBody[0].x * mTileSize.x, snakeBody[0].y * mTileSize.y);
	window.draw(bodyShape, t);

	// Draw body
	Color bodyColor = GetColor();
	bodyColor.a = alpha;
	bodyShape.setFillColor(bodyColor);
	for (size_t i = 1; i < snakeBody.size(); i++)
	{
		bodyShape.setPosition(snakeBody[i].x * mTileSize.x, snakeBody[i].y * mTileSize.y);
		window.draw(bodyShape, t);
	}
}

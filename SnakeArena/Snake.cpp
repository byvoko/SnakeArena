#include "Snake.hpp"

Snake::Snake(Color color, sf::Vector2u startPosition, size_t bodyLen):
	mColor (color),
	mDirection (Direction::Up),
	mBodyLen (bodyLen)
{
	mPositions.push_back(startPosition);
	for (size_t i = 0; i < bodyLen; i++)
	{
		mPositions.push_back({ startPosition.x, startPosition.y + 1});
	}
}

void Snake::Update()
{
}

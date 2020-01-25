#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

class Snake
{
public:
	typedef sf::Vector2u Position;
	typedef std::vector<Position> Positions;
	typedef sf::Color Color;

private:

	enum Direction
	{
		Up,
		Right,
		Down,
		Left,
	};

	Positions mPositions; // Head is the first one
	Color mColor;
	Color mHeadColor;
	Direction mDirection;
	size_t mBodyLen;

	void Move(Position newHeadPosition);

public:
	Snake(Color color, sf::Vector2u startPosition, size_t bodyLen = 3);
	virtual ~Snake();

	Positions& GetBody() { return mPositions; }
	Color& GetColor() { return mColor; }
	Color& GetHeadColor() { return mHeadColor; }

	void Update();
};


#pragma once

#include <SFML/Graphics.hpp>

class Snake
{
private:
	struct Position
	{
		int x, y;
	};

	enum Direction
	{
		Up,
		Right,
		Down,
		Left,
	};

	std::vector<Position> mPositions;
	int mColor;
	Direction mDirection;

	sf::Sprite mBody;

public:
	Snake();
	virtual ~Snake();
};


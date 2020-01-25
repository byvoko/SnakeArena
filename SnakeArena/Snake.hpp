#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

class Snake
{
public:
	typedef std::vector<sf::Vector2u> Position;
	typedef int	Color;

private:

	enum Direction
	{
		Up,
		Right,
		Down,
		Left,
	};

	Position mPositions;
	Color mColor;
	Direction mDirection;
	size_t mBodyLen;	

public:
	Snake(Color color, sf::Vector2u startPosition, size_t bodyLen = 3);
	virtual ~Snake();

	std::pair<Position, Color> GetBody() { return { mPositions, mColor }; }

	void Update();
};


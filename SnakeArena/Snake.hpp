#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

#include "IControls.hpp"

class Snake
{
public:
	typedef sf::Vector2u Position;
	typedef std::vector<Position> Positions;
	typedef sf::Color Color;

	enum Direction
	{
		Up,
		Right,
		Down,
		Left,
	};

private:

	Positions mPositions; // Head is the first one
	Color mColor;
	Direction mDirection;
	Direction mTempDirection;
	size_t mBodyLen;

	ISnakeControls * mControl;

	void Move(Position newHeadPosition);
	void ProcessDirectionChange();

public:
	Snake(Color color, sf::Vector2u startPosition, size_t bodyLen = 3);
	virtual ~Snake();

	std::pair<Positions, Color> GetBody() { return { mPositions, mColor }; }

	void Update();

	void AddControl(ISnakeControls & c);

	void ChangeDirection(Direction d);
};


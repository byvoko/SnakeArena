#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

#include "IGameDrawable.hpp"
#include "IControls.hpp"
#include "Types.hpp"

class Snake :
	public IGameDrawable
{
public:
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
	Color mHeadColor;
	Direction mDirection;
	Direction mTempDirection;

	sf::Vector2f mTileSize;

	size_t mBodyLen;

	ISnakeControls * mControl;

	void Move(Position newHeadPosition);
	void ProcessDirectionChange();

public:
	Snake(Color color, sf::Vector2u startPosition, sf::Vector2f tileSize, size_t bodyLen = 10);
	virtual ~Snake();

	Positions& GetBody() { return mPositions; }
	Color& GetColor() { return mColor; }
	Color& GetHeadColor() { return mHeadColor; }

	void Update();

	void AddControl(ISnakeControls & c);

	void IncrementLength();

	void ChangeDirection(Direction d);

	// Dìdí se pøes IGameDrawable.
	void Draw(sf::RenderWindow & window, sf::Transform t) override;
};


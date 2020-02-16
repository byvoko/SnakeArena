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

	uint64_t mNextUpdateId;
	uint8_t mUpdateIdStep;

	ISnakeControls * mControl;

	bool mNitroEnable;
	uint8_t mStamina;

	void Move(Position newHeadPosition);
	void ProcessDirectionChange();

public:
	static const uint8_t MaxStamina;

	Snake(Color color, sf::Vector2u startPosition, sf::Vector2f tileSize, size_t bodyLen = 10);
	virtual ~Snake();

	Positions const & GetBody() { return mPositions; }
	Color const & GetColor() { return mColor; }
	Color const & GetHeadColor() { return mHeadColor; }

	bool ShouldUpdate(const uint64_t& updateId);
	void Update(const uint64_t& updateId);

	void AddControl(ISnakeControls & c);

	void IncrementLength();

	void ChangeDirection(Direction d);

	void EnableNitro() { mNitroEnable = true; }
	void DisableNitro() { mNitroEnable = false; }

	Position GetNext();

	uint8_t GetStamina();

	// Dìdí se pøes IGameDrawable.
	virtual void Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha = 255) override;
};


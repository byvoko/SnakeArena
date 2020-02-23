#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

#include "IGameDrawable.hpp"
#include "IControls.hpp"
#include "Types.hpp"

class EatEffect; // Forward declaration

class Snake : public IGameDrawable
{
public:
	enum class Direction
	{
		Up,
		Down,
		Right,
		Left,
	};

private:
	Positions mPositions; // Head is the first one
	Color mColor;
	Color mHeadColor;
	Snake::Direction mDirection;
	Snake::Direction mTempDirection;

	sf::Vector2f mTileSize;

	size_t mBodyLen;

	uint64_t mNextUpdateId;
	uint8_t mUpdateIdStep;

	ISnakeControls * mControl;

	bool mNitroEnable;
	bool mNitronYank;
	uint8_t mStamina;

	// TEST: EatEffect
	EatEffect* pEatEffect;

	void Move(Position newHeadPosition);
	void ProcessDirectionChange();

public:
	static const uint8_t MaxStamina;

	Snake(Color color, size_t bodyLen = 3); // sf::Vector2u startPosition, sf::Vector2f tileSize, 
	virtual ~Snake();

	void InitSnake(sf::Vector2f tileSize, sf::Vector2u startPosition);

	Positions const & GetBody() { return mPositions; }
	Color const & GetColor() { return mColor; }
	Color const & GetHeadColor() { return mHeadColor; }

	bool ShouldUpdate(const uint64_t& updateId);
	void Update(const uint64_t& updateId);

	void AddControl(ISnakeControls & c);

	void IncrementLength();
	void RestoreStamina(uint8_t stamina);

	void ChangeDirection(Snake::Direction d);

	void EnableNitro() { mNitroEnable = true; mNitronYank = true; }
	void DisableNitro() { mNitroEnable = false; }

	size_t GetLength() { return mPositions.size(); }
	Snake::Direction GetDirection() { return mTempDirection; }
	uint64_t GetNextUpdateId() { return mNextUpdateId; }

	Position GetNext();

	uint8_t GetStamina();

	// Dìdí se pøes IGameDrawable.
	virtual void Draw(sf::RenderWindow & window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;
};

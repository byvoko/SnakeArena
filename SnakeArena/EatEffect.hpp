#pragma once

#include "IGameDrawable.hpp"

#include "Snake.hpp"

class EatEffect : IGameDrawable
{
private:
	uint64_t mLifeTimePassed;
	uint64_t mLifeTime;

	sf::RectangleShape mRectangles[6];
	Snake::Direction mDirection;

public:
	EatEffect(Position position, sf::Vector2f gridTileSize, Color color, Snake::Direction direction, uint64_t lifeTime);
	virtual ~EatEffect();

	bool HasLifetimeEnded() const;

	void Update();

	// Dìdí se pøes IGameDrawable.
	virtual void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;

};

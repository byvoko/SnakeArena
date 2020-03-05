#pragma once

#include <SFML\Graphics.hpp>

#include "IGameDrawable.hpp"

class GameStartCountdown : public IGameDrawable
{
private:
	sf::Clock mCountdownClock;

protected:
	float mStartCountdownTime; // [s]
	float mCurrentTime; // [s]

public:
	GameStartCountdown(float startTime);

	bool IsActive();
	float GetCurrentTime();

	void Update();
	virtual void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;
};


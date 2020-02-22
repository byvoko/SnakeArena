#pragma once

#include "IGameContent.hpp"

class GameContext : public IGameContent
{
private:
	IGameContent* mpGameContent;
	sf::Vector2u mWindowSize;

public:
	GameContext(sf::Vector2u windowSize);
	~GameContext();

	void Sleep();

	// Dìdí se pøes IGameContent.
	virtual void ProcessEvent(sf::Event e) override;

	virtual void Update() override;
	virtual void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;
};

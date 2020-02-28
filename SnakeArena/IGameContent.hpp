#pragma once

#include <SFML\Graphics.hpp>

#include "IGameDrawable.hpp"
#include "IControls.hpp"

class IGameContent : public IGameDrawable, public IGameControls
{
public:
	virtual void ProcessEvent(sf::Event e) = 0;

	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) = 0;
	virtual sf::Time GetSleepTime() = 0;
};

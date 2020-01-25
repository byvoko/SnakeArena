#pragma once

#include "IControls.hpp"

#include <SFML/Graphics.hpp>

class GamepadControls:
	public ISnakeControls,
	public IGameControls
{
private:
	int mGamepadID;
public:
	GamepadControls(int gamepadID);
	virtual ~GamepadControls();

	void ProcessEvent(sf::Event e) override;
};


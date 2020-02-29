#pragma once
#include <cstdint>

#include <SFML/Graphics.hpp>
#include "MenuSelect.hpp"

class PlayerInputSelector
{
private:
	uint8_t mPlayerID;
	MenuSelect mSelector;
	bool mGamepadConnected[sf::Joystick::Count];
public:
	PlayerInputSelector(uint8_t playerID, MenuItem::Settings bs, sf::Font& font);

	void Update();

	MenuSelect& GetSelector() { return mSelector; }
};


#pragma once
#include <functional>
#include <SFML\Graphics.hpp>

typedef sf::Vector2u			Position;
typedef std::vector<Position>	Positions;
typedef sf::Color				Color;
typedef std::function<void()> Event;

enum PlayerInputs : uint32_t
{
	None = 0,
	Keyboard1,
	Keyboard2,
	Gamepad1,
	Gamepad2,
	Gamepad3,
	Gamepad4,
	Gamepad5,
	Gamepad6,
	Gamepad7,
	Gamepad8,
};

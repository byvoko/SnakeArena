#pragma once

#include <SFML/Graphics.hpp>

class MenuControlsLayout
{
public:
	// Keyboard
	static constexpr sf::Keyboard::Key UpKey = sf::Keyboard::Up;
	static constexpr sf::Keyboard::Key RightKey = sf::Keyboard::Right;
	static constexpr sf::Keyboard::Key DownKey = sf::Keyboard::Down;
	static constexpr sf::Keyboard::Key LeftKey = sf::Keyboard::Left;
	static constexpr sf::Keyboard::Key SelectKey = sf::Keyboard::Enter;
	static constexpr sf::Keyboard::Key EscapeKey = sf::Keyboard::Escape;

	// Gamepad
	static constexpr int SelectButton = 0;
	static constexpr float PovAxisTresh = 50.f;
};
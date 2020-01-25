#pragma once

#include "IControls.hpp"
#include <SFML/Graphics.hpp>

class KeyControls:
	public ISnakeControls,
	public IGameControls
{
private:
	sf::Keyboard::Key mUpKey;
	sf::Keyboard::Key mLeftKey;
	sf::Keyboard::Key mDownKey;
	sf::Keyboard::Key mRightKey;

public:
	KeyControls(sf::Keyboard::Key upKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key downKey, sf::Keyboard::Key rightKey);
	virtual ~KeyControls();

	void ProcessEvent(sf::Event e) override;
};


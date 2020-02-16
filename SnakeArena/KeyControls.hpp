#pragma once

#include <SFML/Graphics.hpp>

#include "IControls.hpp"

class KeyControls :
	public ISnakeControls,
	public IGameControls
{
private:
	sf::Keyboard::Key mUpKey;
	sf::Keyboard::Key mLeftKey;
	sf::Keyboard::Key mDownKey;
	sf::Keyboard::Key mRightKey;
	sf::Keyboard::Key mNitroKey;

public:
	KeyControls(sf::Keyboard::Key upKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key downKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key nitroKey);
	virtual ~KeyControls();

	void ProcessEvent(sf::Event e) override;
};


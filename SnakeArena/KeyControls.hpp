#pragma once

#include <SFML/Graphics.hpp>

#include "IControls.hpp"

class KeyControls :
	public ISnakeControls,
	public IGameControls
{
private:
	sf::Keyboard::Key mUpKey;
	bool mUpKeyIsPressed;
	sf::Keyboard::Key mLeftKey;
	bool mLeftKeyIsPressed;
	sf::Keyboard::Key mDownKey;
	bool mDownKeyIsPressed;
	sf::Keyboard::Key mRightKey;
	bool mRightKeyIsPressed;
	sf::Keyboard::Key mNitroKey;
	bool mNitroKeyIsPressed;

public:
	KeyControls(sf::Keyboard::Key upKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key downKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key nitroKey);
	virtual ~KeyControls();

	void ProcessEvent(sf::Event e) override;

private:
	void PushKey(sf::Keyboard::Key);
	void PullKey(sf::Keyboard::Key);
};


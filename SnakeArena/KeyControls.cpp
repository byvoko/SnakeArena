#include "KeyControls.hpp"


KeyControls::KeyControls(sf::Keyboard::Key upKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key downKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key nitroKey):
	mUpKey (upKey),
	mRightKey (rightKey),
	mDownKey (downKey),
	mLeftKey (leftKey),
	mNitroKey(nitroKey)
{
}

KeyControls::~KeyControls()
{
}

void KeyControls::ProcessEvent(sf::Event e)
{
	if (e.type != sf::Event::KeyPressed)
		return;

	sf::Keyboard::Key key = e.key.code;

	if (key == mUpKey && UpEvent)
		UpEvent();
	else if (key == mRightKey && RightEvent)
		RightEvent();
	else if (key == mDownKey && DownEvent)
		DownEvent();
	else if (key == mLeftKey)
		LeftEvent();
	else if (key == mNitroKey)
		NitroEvent();
}

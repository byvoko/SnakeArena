#include "KeyControls.hpp"

KeyControls::KeyControls(sf::Keyboard::Key upKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key downKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key nitroKey):
	mUpKey (upKey),
	mRightKey (rightKey),
	mDownKey (downKey),
	mLeftKey (leftKey),
	mNitroKey(nitroKey)
{
	mUpKeyIsPressed = mRightKeyIsPressed = mDownKeyIsPressed = mLeftKeyIsPressed = mNitroKeyIsPressed = false;
}

KeyControls::~KeyControls()
{
}

void KeyControls::ProcessEvent(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed)
		PushKey(e.key.code);

	if (e.type == sf::Event::KeyReleased)
		PullKey(e.key.code);

}

void KeyControls::PushKey(sf::Keyboard::Key key)
{
	if (key == mUpKey && UpEvent && !mUpKeyIsPressed)
	{
		mUpKeyIsPressed = true;
		UpEvent();
	}
	else if (key == mRightKey && RightEvent && !mRightKeyIsPressed)
	{
		mRightKeyIsPressed = true;
		RightEvent();
	}
	else if (key == mDownKey && DownEvent && !mDownKeyIsPressed)
	{
		mDownKeyIsPressed = true;
		DownEvent();
	}
	else if (key == mLeftKey && LeftEvent && !mLeftKeyIsPressed)
	{
		mLeftKeyIsPressed = true;
		LeftEvent();
	}
	else if (key == mNitroKey && NitroEventPush && !mNitroKeyIsPressed)
	{
		mNitroKeyIsPressed = true;
		NitroEventPush();
	}

}

void KeyControls::PullKey(sf::Keyboard::Key key)
{

	if (key == mUpKey)
	{
		mUpKeyIsPressed = false;
	}
	else if (key == mRightKey)
	{
		mRightKeyIsPressed = false;
	}
	else if (key == mDownKey)
	{
		mDownKeyIsPressed = false;
	}
	else if (key == mLeftKey)
	{
		mLeftKeyIsPressed = false;
	}
	else if (key == mNitroKey)
	{
		mNitroKeyIsPressed = false;
		if (NitroEventPull)
			NitroEventPull();
	}
}
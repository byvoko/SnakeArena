#include "GamepadControls.hpp"

#include <iostream>

GamepadControls::GamepadControls(int gamepadID, int nitroButton):
	mGamepadID (gamepadID),
	mNitroButton (nitroButton)
{
	if (!sf::Joystick::isConnected(gamepadID))
		return;

	mButtonsCount = sf::Joystick::getButtonCount(gamepadID);
}


GamepadControls::~GamepadControls()
{
}

void GamepadControls::processButton(const bool isPressedNow, bool & isPressed, std::function<void()> & cb)
{
	if (isPressedNow && !isPressed && cb)
	{
		isPressed = true;
		cb();
	}
	else if (!isPressedNow && isPressed)
		isPressed = false;
}

void GamepadControls::ProcessEvent(sf::Event e)
{
	const float x = sf::Joystick::getAxisPosition(mGamepadID, sf::Joystick::PovX);
	const float y = sf::Joystick::getAxisPosition(mGamepadID, sf::Joystick::PovY);

	const bool upPressed = y >= PovAxisTresh;
	const bool downPressed = y <= (-1 * PovAxisTresh);
	const bool leftPressed = x <= (-1 * PovAxisTresh);
	const bool rightPressed = x >= PovAxisTresh;
	const bool nitroIsPressed = sf::Joystick::isButtonPressed(mGamepadID, mNitroButton);
	
	processButton(upPressed, mUpIsPressed, UpEvent);
	processButton(downPressed, mDownIsPressed, DownEvent);
	processButton(rightPressed, mRightIsPressed, RightEvent);
	processButton(leftPressed, mLeftIsPressed, LeftEvent);
	/*
	if (upPressed && !mUpIsPressed && UpEvent)
	{
		mUpIsPressed = true;
		UpEvent();
	}
	else if (!upPressed && mUpIsPressed)
	{
		mUpIsPressed = false;
	}

	if (downPressed && !mDownIsPressed && DownEvent)
	{
		mDownIsPressed = true;
		DownEvent();
		
	}
	else if (!downPressed && mDownIsPressed)
	{
		mDownIsPressed = false;
	}

	if (leftPressed && !mLeftIsPressed && LeftEvent)
	{
		mLeftIsPressed = true;
		DownEvent();

	}
	else if (!leftPressed && mLeftIsPressed)
	{
		mLeftIsPressed = false;
	}

	if (rightPressed && !mRightIsPressed && RightEvent)
	{
		mRightIsPressed = true;
		RightEvent();

	}
	else if (!rightPressed && mLeftIsPressed)
	{
		mRightIsPressed = false;
	}
	*/
	if (nitroIsPressed && !mNitroIsPressed)
	{
		mNitroIsPressed = true;
		NitroEventPush();
	}
	else if (!nitroIsPressed && mNitroIsPressed)
	{
		mNitroIsPressed = false;
		NitroEventPull();
	}
}

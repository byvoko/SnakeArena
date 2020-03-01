#include "MenuControls.hpp"

#include "MenuControlsLayout.hpp"

MenuControls::MenuControls()
{

}

void MenuControls::ProcessEvent(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		ProcessKeyboardPushEvent(e.key.code);
	}
	for (int i = 0; i < sf::Joystick::Count; i++)
	{
		if (sf::Joystick::isConnected(i))
		{
			ProcessGamePad(i);
		}
	}
	
}

void MenuControls::ProcessButton(const bool isPressedNow, bool& isPressed, std::function<void()>& cb)
{
	if (isPressedNow && !isPressed && cb)
	{
		isPressed = true;
		cb();
	}
	else if (!isPressedNow && isPressed)
		isPressed = false;
}

void MenuControls::ProcessGamePad(int gamepadID)
{
	const float x = sf::Joystick::getAxisPosition(gamepadID, sf::Joystick::PovX);
	const float y = sf::Joystick::getAxisPosition(gamepadID, sf::Joystick::PovY);

	const bool upPressed = y >= MenuControlsLayout::PovAxisTresh;
	const bool downPressed = y <= (-1 * MenuControlsLayout::PovAxisTresh);
	const bool leftPressed = x <= (-1 * MenuControlsLayout::PovAxisTresh);
	const bool rightPressed = x >= MenuControlsLayout::PovAxisTresh;
	const bool selectIsPressed = sf::Joystick::isButtonPressed(gamepadID, MenuControlsLayout::SelectButton);

	ProcessButton(upPressed, mGamepadUpIsPressed[gamepadID], UpEvent);
	ProcessButton(downPressed, mGamepadDownIsPressed[gamepadID], DownEvent);
	ProcessButton(rightPressed, mGamepadRightIsPressed[gamepadID], RightEvent);
	ProcessButton(leftPressed, mGamepadLeftIsPressed[gamepadID], LeftEvent);
	ProcessButton(selectIsPressed, mGamepadSelectIsPressed[gamepadID], SelectEvent);

}

void MenuControls::ProcessKeyboardPushEvent(sf::Keyboard::Key key)
{
	switch (key)
	{
		case MenuControlsLayout::UpKey:
			if (UpEvent)
				UpEvent();
			break;
		case MenuControlsLayout::RightKey:
			if (RightEvent)
				RightEvent();
			break;
		case MenuControlsLayout::LeftKey:
			if (LeftEvent)
				LeftEvent();
			break;
		case MenuControlsLayout::DownKey:
			if (DownEvent)
				DownEvent();
			break;
		case MenuControlsLayout::SelectKey:
			if (SelectEvent)
				SelectEvent();
			break;
	}
}

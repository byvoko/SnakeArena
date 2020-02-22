#pragma once
#include <functional>

#include "IControls.hpp"

class MenuControls : public IGameControls
{
private:
	void ProcessKeyboardPushEvent(sf::Keyboard::Key key);
	void ProcessGamePad(int gamepadID);
	void ProcessButton(const bool isPressedNow, bool& isPressed, std::function<void()>& cb);

	bool mGamepadUpIsPressed[sf::Joystick::Count];
	bool mGamepadRightIsPressed[sf::Joystick::Count];
	bool mGamepadDownIsPressed[sf::Joystick::Count];
	bool mGamepadLeftIsPressed[sf::Joystick::Count];
	bool mGamepadSelectIsPressed[sf::Joystick::Count];

public:
	std::function<void()> UpEvent;
	std::function<void()> RightEvent;
	std::function<void()> DownEvent;
	std::function<void()> LeftEvent;
	std::function<void()> SelectEvent;

	MenuControls();

	void ProcessEvent(sf::Event e) override;
};


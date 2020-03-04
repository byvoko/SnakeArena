#pragma once

#include "IControls.hpp"

#include <SFML/Graphics.hpp>

class GamepadControls : public IControls
{
private:
	static constexpr float PovAxisTresh = 50.f;
	int mGamepadID;
	int mButtonsCount;

	bool mUpIsPressed;
	bool mLeftIsPressed;
	bool mDownIsPressed;
	bool mRightIsPressed;
	int mNitroButton;
	bool mNitroIsPressed;

	void processButton(const bool isPressedNow, bool & isPressed, std::function<void()> & cb);

public:
	GamepadControls(int gamepadID, int nitroButton);
	virtual ~GamepadControls();

	void ProcessEvent(sf::Event e) override;
};


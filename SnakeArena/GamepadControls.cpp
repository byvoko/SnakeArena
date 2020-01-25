#include "GamepadControls.hpp"



GamepadControls::GamepadControls(int gamepadID):
	mGamepadID(gamepadID)
{
}


GamepadControls::~GamepadControls()
{
}

void GamepadControls::ProcessEvent(sf::Event e)
{
	/*float x = sf::Joystick::getAxisPosition(mGamepadID, sf::Joystick::X);
	float y = sf::Joystick::getAxisPosition(mGamepadID, sf::Joystick::Y);

	if (x > 0 && LeftEvent)
		LeftEvent();
	else if (x < 0 && RightEvent)
		RightEvent();
	else if (y > 0 && UpEvent)
		UpEvent();
	else if (y < 0 && DownEvent)
		DownEvent();*/

	if (sf::Joystick::isButtonPressed(mGamepadID, 9) && UpEvent)
		LeftEvent();

}

#include "PlayerInputSelector.hpp"
#include "Types.hpp"

PlayerInputSelector::PlayerInputSelector(uint8_t playerID, MenuItem::Settings bs, sf::Font& font) :
	mPlayerID(playerID),
	mSelector("Player " + std::to_string(playerID), font, bs, {}, 0)
{
	MenuSelect::Item iKeyboard1 = { "Keyboard 1", PlayerInputs::Keyboard1 };
	MenuSelect::Item iKeyboard2 = { "Keyboard 2", PlayerInputs::Keyboard2 };
	mSelector.AddItem(iKeyboard1);
	mSelector.AddItem(iKeyboard2);
	for (int i = 0; i < sf::Joystick::Count; i++)
		mGamepadConnected[i] = false;
}

void PlayerInputSelector::Update()
{
	for (int i = 0; i < sf::Joystick::Count; i++)
	{
		const bool isConnected = sf::Joystick::isConnected(i);
		const MenuSelect::Value value = PlayerInputs::Gamepad1 + i;

		if (isConnected && !mGamepadConnected[i])
		{
			mGamepadConnected[i] = true;
			MenuSelect::Item ig = { "Gamepad " + std::to_string(i), value };
			mSelector.AddItem(ig);
		}
		else if (!isConnected && mGamepadConnected[i])
		{
			mGamepadConnected[i] = false;
			mSelector.RemoveItemByValue(value);
		}
	}

	mSelector.Update();
}
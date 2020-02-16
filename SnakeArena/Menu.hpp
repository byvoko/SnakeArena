#pragma once

#include "IGameDrawable.hpp"
class Menu : public IGameDrawable
{
private:
	enum State
	{
		None = 0,
		Pause,
		Exit
	};

	State mState;
public:
	Menu();

	void Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha = 255) override;
};
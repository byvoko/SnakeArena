#pragma once

#include "IGameDrawable.hpp"
#include "MenuControls.hpp"

class Menu : public IGameDrawable, public IGameControls
{
private:
	const std::string Font = "Anyfreak.ttf";
	sf::Font mFont;

	MenuControls mControls;

	enum State
	{
		TopLevel = 0,
		NewGame
	};
	State mState;
	int mSelectedItemIdx;

	void DrawTopLevel(sf::RenderWindow& window, sf::Transform t, uint8_t alpha = 255);
	void DrawNewGame(sf::RenderWindow& window, sf::Transform t, uint8_t alpha = 255);
public:
	Menu();

	void Draw(sf::RenderWindow & window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;

	void Update();
	void ProcessEvent(sf::Event e) override;
};
#pragma once

#include <vector>
#include "IGameContent.hpp"
#include "MenuControls.hpp"
#include "MenuButton.hpp"

class Menu : public IGameContent
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
	std::vector<MenuButton> mTopLevelButtons;

	void DrawTopLevel(sf::RenderWindow& window, sf::Transform t, uint8_t alpha = 255);
	void DrawNewGame(sf::RenderWindow& window, sf::Transform t, uint8_t alpha = 255);
public:
	Menu();

	void Draw(sf::RenderWindow & window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;

	void Update() override;
	void ProcessEvent(sf::Event e) override;

	void ChangeSelectedItem(bool goUp);

	virtual sf::Time GetSleepTime() override;
};
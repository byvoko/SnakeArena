#pragma once

#include <vector>
#include "IGameContent.hpp"
#include "MenuControls.hpp"
#include "TopLevelMenu.hpp"
#include "NewGameMenu.hpp"
#include "IMenuContainer.hpp"

class Menu : public IGameContent
{
private:
	const std::string Font = "font.ttf";
	sf::Font mFont;

	MenuControls mControls;
	TopLevelMenu mTopLevelMenu;
	NewGameMenu mNewGameMenu;
	IMenuContainer* mActiveMenu;

public:
	Menu();

	void Draw(sf::RenderWindow & window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;

	void Update() override;
	void ProcessEvent(sf::Event e) override;

	void ChangeSelectedItem(bool goUp);
};
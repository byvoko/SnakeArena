#pragma once

#include <vector>
#include "IGameContent.hpp"
#include "MenuControls.hpp"
#include "MenuItem.hpp"
#include "PlayerInputSelector.hpp"

class Menu : public IGameContent
{
private:
	const std::string Font = "Anyfreak.ttf";
	sf::Font mFont;

	MenuControls mControls;

	typedef std::vector<MenuItem*>	vMenu;
	vMenu mTopLevelButtons;
	vMenu mNewGameItems;
	vMenu* mActiveMenu;

	std::vector<PlayerInputSelector *> mPlayersIS;

public:
	Menu();

	void Draw(sf::RenderWindow & window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;

	void Update() override;
	void ProcessEvent(sf::Event e) override;

	void ChangeSelectedItem(bool goUp);
};
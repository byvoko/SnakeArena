#pragma once

#include <SFML/Graphics.hpp>

#include "Types.hpp"
#include "IMenuContainer.hpp"
#include "PlayerInputSelector.hpp"

class NewGameMenu :
	public IMenuContainer
{
private:
	std::vector<PlayerInputSelector *> mPlayersIS;
public:
	NewGameMenu();

	void Init(MenuItem::Settings ItemsSettings, sf::Font& font) override;

	void Update() override;
	void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;

	void SetOnClickEventBack(Event e);
};


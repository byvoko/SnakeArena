#pragma once

#include <SFML/Graphics.hpp>

#include "Types.hpp"
#include "IMenuContainer.hpp"

class TopLevelMenu : 
	public IMenuContainer
{
public:
	TopLevelMenu();

	void SetOnClickEventNewGame(Event e);
	void SetOnClickEventExtiGame(Event e) {}

	void Init(MenuItem::Settings ItemsSettings, sf::Font& font) override;

	void Update() override;
	void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;

};


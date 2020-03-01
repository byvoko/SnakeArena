#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "Types.hpp"
#include "MenuItem.hpp"
#include "IGameDrawable.hpp"

class MenuButton : 
	public MenuItem
{
private:
	sf::Text mText;
	Event mOnClickEvent;

public:
	MenuButton(std::string s, sf::Font & font, MenuItem::Settings settings);

	void SetOnClickEvent(Event e) { mOnClickEvent = e; }

	void Click() override;
	void Swap(bool Right) override {}

	void Update() override {}

	void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) final;
};


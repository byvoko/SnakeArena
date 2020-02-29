#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "MenuItem.hpp"
#include "IGameDrawable.hpp"

class MenuButton : 
	public MenuItem
{
private:
	sf::Text mText;

public:
	MenuButton(std::string s, sf::Font & font, MenuItem::Settings settings);

	void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) final;
};


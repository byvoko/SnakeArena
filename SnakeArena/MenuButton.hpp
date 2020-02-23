#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "IGameDrawable.hpp"

class MenuButton : public IGameDrawable
{
public:
	struct ButtonSettings
	{
		int fontSize;
		int boxOutlineSize;
		int selectedBoxOutlineSize;
		sf::Vector2f boxSize;

		sf::Color textColor;
		sf::Color backgroundColor;
		sf::Color boxOutlineColor;

		sf::Color selectedTextColor;
		sf::Color selectedBoxOutlineColor;
		sf::Color selectedBackgroundColor;
		
	};
private:
	ButtonSettings mSettings;
	sf::RectangleShape mBackground;
	sf::Text mText;
	bool mIsSelected;

public:
	MenuButton(std::string s, sf::Font & font, ButtonSettings settings);

	void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;

	inline bool IsSelected() { return mIsSelected; }
	void Select();
	void Unselect();
	ButtonSettings GetSettings() { return mSettings; }
	sf::Vector2f GetSize() { return mSettings.boxSize; }

};


#pragma once

#include <SFML/Graphics.hpp>
#include "IGameDrawable.hpp"

class MenuItem /*:
	public IGameDrawable*/
{
public:
	struct Settings
	{
		bool isVisible;
		int fontSize;
		int boxOutlineSize;
		int selectedBoxOutlineSize;
		sf::Vector2f boxSize;

		sf::Color textColor;
		sf::Color backgroundColor;
		sf::Color boxOutlineColor;

		sf::Color selectedBoxOutlineColor;
		sf::Color selectedBackgroundColor;

	};

protected:
	Settings mSettings;

	sf::RectangleShape mBackground;
	bool mIsSelected;

public:

	MenuItem(Settings s) :
		mSettings(s)
	{
		Unselect();
		mBackground.setSize(mSettings.boxSize);
	}

	sf::Vector2f GetSize() { return mSettings.boxSize; };
	inline bool IsSelected() { return mIsSelected; }

	void Select()
	{
		mIsSelected = true;
		mBackground.setFillColor(mSettings.selectedBackgroundColor);
		mBackground.setOutlineColor(mSettings.selectedBoxOutlineColor);
		mBackground.setOutlineThickness(mSettings.selectedBoxOutlineSize);
	}

	void Unselect()
	{
		mIsSelected = false;
		mBackground.setFillColor(mSettings.backgroundColor);
		mBackground.setOutlineColor(mSettings.boxOutlineColor);
		mBackground.setOutlineThickness(mSettings.boxOutlineSize);

	}
	Settings GetSettings() { return mSettings; };

	virtual void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) = 0;

};

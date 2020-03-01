#pragma once

#include <SFML/Graphics.hpp>
#include "IGameDrawable.hpp"

class MenuItem :
	public IGameDrawable
{
public:
	struct Settings
	{
		bool isVisible;
		int fontSize;	//TODO
		int boxOutlineSize;
		int selectedBoxOutlineSize;
		sf::Vector2f boxSize;

		sf::Color textColor;	//TODO
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

	bool IsVisible() { return mSettings.isVisible; }
	void Visible(bool v) { mSettings.isVisible = v; }

	virtual void Click() = 0;
	virtual void Swap(bool Right) = 0;
	virtual void Update() = 0;
};

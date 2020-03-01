#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "MenuItem.hpp"
#include "IGameDrawable.hpp"

class MenuSelect :
	public MenuItem
{
public:
	typedef uint32_t Value;
	struct Item
	{
		std::string text;
		Value value;
	};

private:
	std::string mString;
	sf::Text mText;
	std::vector<Item> mItems;
	uint32_t mSelectedItemIdx;

	void CreateText();
public:
	MenuSelect(std::string s, sf::Font& font, MenuItem::Settings settings, std::vector<Item> items, uint32_t selectedItemIdx);

	void Click() override {}
	void Swap(bool Right) override;
	void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) final;

	void AddItem(Item i) {
		mItems.push_back(i); 
		CreateText();
	}
	void RemoveItemByIdx(int idx);
	void RemoveItemByValue(Value v);

	void Update() override;
	Value GetValue() { return mItems[mSelectedItemIdx].value; }
	std::string GetText() { return mItems[mSelectedItemIdx].text; }
};


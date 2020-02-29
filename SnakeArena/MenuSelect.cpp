#include "MenuSelect.hpp"

MenuSelect::MenuSelect(std::string s, sf::Font& font, MenuItem::Settings settings, std::vector<Item> items, uint32_t selectedItemIdx) :
	MenuItem(settings),
	mString (s),
	mItems (items),
	mSelectedItemIdx (selectedItemIdx)
{
	if (items.size() > mSelectedItemIdx)
		mSelectedItemIdx = 0;

	mText.setFont(font);
	mText.setFillColor(settings.textColor);
	mText.setCharacterSize(settings.fontSize);
	Update();
}

void MenuSelect::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	if (!mSettings.isVisible)
		return;

	auto backgroundColor = mBackground.getFillColor();
	backgroundColor.a = alpha;
	mBackground.setFillColor(backgroundColor);
	window.draw(mBackground, t);
	auto textLb = mText.getLocalBounds();
	t.translate({ (mSettings.boxSize.x - textLb.width) / 2.f, ((mSettings.boxSize.y - textLb.height) / 2.f) - textLb.top });
	auto textColor = mText.getFillColor();
	textColor.a = alpha;
	mText.setFillColor(textColor);
	window.draw(mText, t);
}

void MenuSelect::RemoveItemByIdx(int idx)
{
	if (idx >= mItems.size())
		return;

	mItems.erase(mItems.begin() + idx);
}

void MenuSelect::Update()
{
	if (mItems.size() > 0)
		mText.setString(mString + " < " + mItems[mSelectedItemIdx].text + " >");
	else
		mText.setString(mString + " < X >");
}

void MenuSelect::RemoveItemByValue(Value v)
{
	if (mItems.size() == 0)
		return;

	for (int i = 0; i < mItems.size(); i++)
	{
		if (mItems[i].value == v)
			RemoveItemByIdx(i);
	}
}
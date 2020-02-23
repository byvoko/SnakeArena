#include "MenuButton.hpp"

MenuButton::MenuButton(std::string s, sf::Font & font, ButtonSettings settings) :
	mSettings (settings)
{
	mText.setString(s);
	mText.setFont(font);
	mText.setFillColor(settings.textColor);
	mText.setCharacterSize(settings.fontSize);

	Unselect();
	mBackground.setSize(settings.boxSize);

}

void MenuButton::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	auto backgroundColor = mBackground.getFillColor();
	backgroundColor.a = alpha;
	mBackground.setFillColor(backgroundColor);
	window.draw(mBackground, t);

	auto textLb = mText.getLocalBounds();
	t.translate({ (mSettings.boxSize.x - textLb.width) / 2.f, ((mSettings.boxSize.y - textLb.height) / 2.f) - textLb.top});
	auto textColor = mText.getFillColor();
	textColor.a = alpha;
	mText.setFillColor(textColor);
	window.draw(mText, t);
}

void MenuButton::Select()
{
	mIsSelected = true; 
	mBackground.setFillColor(mSettings.selectedBackgroundColor);
	mBackground.setOutlineColor(mSettings.selectedBoxOutlineColor);
	mBackground.setOutlineThickness(mSettings.selectedBoxOutlineSize);

	mText.setFillColor(mSettings.selectedTextColor);
}

void MenuButton::Unselect()
{ 
	mIsSelected = false; 
	mBackground.setFillColor(mSettings.backgroundColor);
	mBackground.setOutlineColor(mSettings.boxOutlineColor);
	mBackground.setOutlineThickness(mSettings.boxOutlineSize);
	
	mText.setFillColor(mSettings.textColor);
}
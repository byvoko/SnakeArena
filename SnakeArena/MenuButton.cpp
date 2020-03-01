#include "MenuButton.hpp"

MenuButton::MenuButton(std::string s, sf::Font & font, MenuItem::Settings settings) :
	MenuItem(settings)
{
	mText.setString(s);
	mText.setFont(font);
	mText.setFillColor(settings.textColor);
	mText.setCharacterSize(settings.fontSize);
}

void MenuButton::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	if (!mSettings.isVisible)
		return;

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

void MenuButton::Click()
{
	if (mOnClickEvent)
		mOnClickEvent();
}
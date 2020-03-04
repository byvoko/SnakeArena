#include "Background.hpp"

Background::Background(const sf::Vector2u& sizePx)
	: mRectangle({ (float)sizePx.x, (float)sizePx.y })
{
	mRectangle.setFillColor(sf::Color(0x27, 0x6B, 0x38));
	mRectangle.setPosition(0, 0);
}

void Background::Update()
{
}

void Background::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	window.draw(mRectangle, t);
}

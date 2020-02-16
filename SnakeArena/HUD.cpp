#include "HUD.hpp"

void HUD::Update()
{
}

void HUD::Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha)
{
	sf::Vector2f hudSize(window.getSize().x, Height);
	sf::RectangleShape background(hudSize);
	background.setFillColor(sf::Color(0, 0, 0));
	t.translate(0, (window.getSize().y - Height));
	window.draw(background, t);
}

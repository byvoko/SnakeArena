#include "GameStartCountdown.hpp"

#include <iomanip>
#include <sstream>

GameStartCountdown::GameStartCountdown(float startTime)
	: mCountdownClock()
	, mStartCountdownTime(startTime)
	, mCurrentTime(startTime)
{
	mCountdownClock.restart();
}

bool GameStartCountdown::IsActive()
{
	return mCurrentTime > 0.0f;
}

float GameStartCountdown::GetCurrentTime()
{
	return mCurrentTime;
}

void GameStartCountdown::Update()
{
	if (IsActive())
	{
		mCurrentTime -= mCountdownClock.getElapsedTime().asSeconds();
		mCountdownClock.restart();
	}
}

void GameStartCountdown::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	if (!IsActive())
		return;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << mCurrentTime;
	std::string s = stream.str();

	sf::Vector2u wSize = window.getSize();

	sf::Font font;
	font.loadFromFile("Anyfreak.ttf");
	sf::Text text;
	text.setString(s);
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
	text.setPosition((wSize.x / 2) - 30, (wSize.y / 2) - 35);

	sf::RectangleShape endBack;
	sf::Color c;
	c = sf::Color::Black;
	c.a = 240;
	endBack.setFillColor(c);
	endBack.setSize({ 90, 80 });
	endBack.setPosition((wSize.x / 2) - (endBack.getSize().x / 2), (wSize.y / 2) - (endBack.getSize().y / 2));

	window.draw(endBack);
	window.draw(text);
}

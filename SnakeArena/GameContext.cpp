#include "GameContext.hpp"

#include <stdio.h>

#include "Game.hpp"
#include "Menu.hpp"

GameContext::GameContext(sf::Vector2u windowSize)
	: mWindowSize(windowSize)
	, mpGameContent(nullptr)
{
	// Init menu
	//mpGameContent = new Menu();

	// Test - Game
	mpGameContent = new Game(windowSize);
}

GameContext::~GameContext()
{
	if (mpGameContent != nullptr)
	{
		delete mpGameContent;
		mpGameContent = nullptr;
	}
}

void GameContext::SetSleep()
{
	sf::Time sleepTime = GetSleepTime();
	if (sleepTime.asMilliseconds() > 0)
		sf::sleep(sleepTime);
}

void GameContext::ProcessEvent(sf::Event e)
{
	mpGameContent->ProcessEvent(e);
}

void GameContext::Update()
{
	mpGameContent->Update();
}

void GameContext::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	mpGameContent->Draw(window, t, alpha);
}

sf::Time GameContext::GetSleepTime()
{
	return mpGameContent->GetSleepTime();
}

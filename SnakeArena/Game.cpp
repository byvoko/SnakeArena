#include "Game.hpp"

void Game::InitArenas()
{
	sf::Vector2u arenaSizePx = { 1200, 700 };
	sf::Vector2u arenaTileSize = { 20, 20 };
	sf::Vector2u arenaGritTileSize = { arenaSizePx.x / arenaTileSize.x, arenaSizePx.y / arenaTileSize.y };
	Arena arena(arenaSizePx, arenaGritTileSize);
	mArenas.push_back(arena);
}

void Game::InitSnakes()
{
	if (mArenas.size() == 0)
		return;

	auto gridTileSize = mArenas[0].GetGridTileSize();
	Snake snake(sf::Color(150, 50, 250), { gridTileSize.x / 2, gridTileSize.y / 2 });
	mSnakes.push_back(snake);
	mArenas[0].AddSnake(mSnakes[0]);
}

Game::Game()
{
	InitArenas();
	InitSnakes();
}

Game::~Game()
{
}

void Game::Draw(sf::RenderWindow & window)
{
	sf::Time elapsed = mClockDraw.getElapsedTime();
	if (elapsed.asMilliseconds() < (1000 / FPS))
		return;

	mClockDraw.restart();

	if (mArenas.size() == 0)
		return;

	window.clear();
	for (Arena & arena : mArenas)
	{
		arena.Draw(window);
	}
	window.display();
}

void Game::Update()
{
	sf::Time elapsed = mClockUpdate.getElapsedTime();
	if (elapsed.asMilliseconds() < mSpeed)
		return;

	mClockUpdate.restart();

	if (mArenas.size() == 0)
		return;

	for (Arena & arena : mArenas)
	{
		arena.Update();
	}
}

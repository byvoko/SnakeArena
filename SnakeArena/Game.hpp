#pragma once

#include <vector>

#include "Arena.hpp"
#include "Snake.hpp"
#include "Background.hpp"
#include "GameInterface.hpp"

class Game
{
private:
	Background mBackground;
	GameInterface mGameInterface;

	std::vector<Arena> mArenas;
	std::vector<Snake> mSnakes;

	static constexpr int FPS = 60;
	int mSpeed = 1000;	//[ms]

	sf::Clock mClockUpdate;
	sf::Clock mClockDraw;

	void InitBackground();
	void InitArenas();
	void InitSnakes();
	void InitGameInterface();

public:
	Game();
	virtual ~Game();

	void Draw(sf::RenderWindow & window);
	void Update();
};

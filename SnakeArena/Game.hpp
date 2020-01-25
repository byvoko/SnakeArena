#pragma once

#include <vector>

#include "Arena.hpp"
#include "Snake.hpp"

class Game
{
private:
	std::vector<Arena> mArenas;
	std::vector<Snake> mSnakes;

	static constexpr int FPS = 60;
	int mSpeed = 1000;	//[ms]

	sf::Clock mClockUpdate;
	sf::Clock mClockDraw;

	void InitArenas();
	void InitSnakes();

public:
	Game();
	virtual ~Game();

	void Draw(sf::RenderWindow & window);
	void Update();
};

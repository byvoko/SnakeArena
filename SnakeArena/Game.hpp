#pragma once

#include <vector>

#include "Arena.hpp"
#include "Snake.hpp"
#include "IControls.hpp"

class Game
{
private:
	std::vector<Arena> mArenas;
	std::vector<Snake> mSnakes;
	std::vector<IGameControls *> mControls;

	static constexpr int FPS = 60;
	int mSpeed = 200;	//[ms]

	sf::Clock mClockUpdate;
	sf::Clock mClockDraw;

	void InitArenas();
	void InitSnakes();

public:
	Game();
	virtual ~Game();

	void Draw(sf::RenderWindow & window);
	void Update();
	void ProcessEvent(sf::Event e);
};

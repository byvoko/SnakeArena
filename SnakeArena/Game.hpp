#pragma once

#include <vector>

#include "Arena.hpp"
#include "Snake.hpp"
#include "Background.hpp"
#include "GameInterface.hpp"

#include "IControls.hpp"
#include "BaseItem.hpp"
#include "FoodItem.hpp"

class Game
{
private:
	Background mBackground;
	GameInterface mGameInterface;

	std::vector<Arena> mArenas;
	std::vector<Snake> mSnakes;
	std::vector<IGameControls *> mControls;

	// Test
	std::vector<BaseItem*> mItems;

	static constexpr int FPS = 60;
	int mSpeed = 200;	//[ms]

	sf::Clock mClockUpdate;
	sf::Clock mClockDraw;

	void InitBackground();
	void InitArenas(sf::Vector2u windowSize);
	void InitSnakes();
	void InitGameInterface();

public:
	Game(sf::Vector2u windowSize);
	virtual ~Game();

	void Draw(sf::RenderWindow & window);
	void Update();
	void ProcessEvent(sf::Event e);
};

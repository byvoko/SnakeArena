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

	bool mRun;
	int mSnakeWinner;

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
	bool CheckSnakeBodyColision(Positions const & snakeBody, const Position nextPosition);
	bool CheckSnakeArenaColision(const Position nextPosition, sf::Vector2u gridSize);

	void UpdateMovement();
	void PrepareEnd();
	void DrawEnd(sf::RenderWindow & window);

public:
	Game(sf::Vector2u windowSize);
	virtual ~Game();

	void Draw(sf::RenderWindow & window);
	void Update();
	void ProcessEvent(sf::Event e);
};

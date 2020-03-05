#pragma once

#include <vector>
#include <list>
#include <string>

#include "IGameContent.hpp"

#include "Arena.hpp"
#include "Snake.hpp"
#include "Background.hpp"
#include "HUD.hpp"

#include "IControls.hpp"
#include "BaseItem.hpp"
#include "FoodItem.hpp"
#include "GameStartCountdown.hpp"

class Game : public IGameContent
{
public:
	static const std::string GameFont;

private:
	std::list<Arena> mArenas;
	std::list<Snake> mSnakes;
	std::vector<IControls*> mControls;

	bool mRun;
	GameStartCountdown mGameStartCountdown;
	Snake* pSnakeWinner;

	// Test
	FoodItem* pFood;

	static constexpr int FoodLevelingScale = 7;	//Po kazdem x jidle nastane dalsi level
	static constexpr float FrameTimeMs = 1000.f / 60;
	int mSpeed = 20;	//[ms]
	int nextSpeedAcumulator;
	uint64_t mUpdateId;

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

	void GenerateFood();
	bool IsFoodOnSnake(Position& position);

public:
	Game(sf::Vector2u windowSize);
	virtual ~Game();

	// Dìdí se pøes IGameContent.
	void ProcessEvent(sf::Event e);

	void Update();
	virtual void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) override;

	virtual sf::Time GetSleepTime() override;

	virtual void Resize(sf::Vector2u windowSize) override;
};

#pragma once

#include <vector>
#include <string>

#include "IGameContent.hpp"

#include "Arena.hpp"
#include "Snake.hpp"
#include "Background.hpp"
#include "HUD.hpp"

#include "IControls.hpp"
#include "BaseItem.hpp"
#include "FoodItem.hpp"
#include "EatEffect.hpp"

class Game : public IGameContent
{
public:
	static const std::string GameFont;

private:
	Background mBackground;
	HUD mHud;

	std::vector<Arena> mArenas;
	std::vector<Snake> mSnakes;
	std::vector<IGameControls*> mControls;

	bool mRun;
	int mSnakeWinner;

	// Test
	FoodItem* pFood;
	EatEffect* pEatEffect;

	int mSpeed = 20;	//[ms]
	uint64_t mUpdateId;

	sf::Clock mClockUpdate;

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
};

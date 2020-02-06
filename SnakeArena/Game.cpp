#include "Game.hpp"
#include "KeyControls.hpp"
#include "GamepadControls.hpp"

void Game::InitBackground()
{
	mBackground = Background();
}

void Game::InitArenas(sf::Vector2u windowSize)
{
	sf::Vector2u arenaSizePx = { (windowSize.x / 2), windowSize.y };
	sf::Vector2u arenaTileSize = { 20, 20 };
	sf::Vector2u arenaGritTileSize = { arenaSizePx.x / arenaTileSize.x, arenaSizePx.y / arenaTileSize.y };
	
	Arena arena1(arenaSizePx, arenaGritTileSize, sf::Vector2u(0, 0));
	Arena arena2(arenaSizePx, arenaGritTileSize, sf::Vector2u((windowSize.x / 2), 0));

	mArenas.push_back(arena1);
	mArenas.push_back(arena2);
}

void Game::InitSnakes()
{
	if (mArenas.size() == 0)
		return;

	auto gridTileSize = mArenas[0].GetGridTileSize();

	Snake snake1(sf::Color(150, 50, 250), { gridTileSize.x / 2, gridTileSize.y / 2 }, mArenas[0].CalcTileSize());
	Snake snake2(sf::Color(200, 25, 180), { gridTileSize.x / 2, gridTileSize.y / 2 }, mArenas[1].CalcTileSize());

	mSnakes.push_back(snake1);
	mSnakes.push_back(snake2);

	mArenas[0].AddSnake(mSnakes[0]);
	mArenas[1].AddSnake(mSnakes[1]);

	KeyControls * key1 = new KeyControls(sf::Keyboard::Key::W, sf::Keyboard::Key::D, sf::Keyboard::Key::S, sf::Keyboard::Key::A);
	mSnakes[0].AddControl(*key1);
	mControls.push_back(key1);
	
	KeyControls * key2 = new KeyControls(sf::Keyboard::Key::Up, sf::Keyboard::Key::Right, sf::Keyboard::Key::Down, sf::Keyboard::Key::Left);
	mSnakes[1].AddControl(*key2);
	mControls.push_back(key2);

	/*if (sf::Joystick::isConnected(0))
	{
		GamepadControls * gamepad = new GamepadControls(0);
		mSnakes[0].AddControl(*gamepad);
		mControls.push_back(gamepad);
	}*/
}

void Game::InitGameInterface()
{
	mGameInterface = GameInterface();
}

void Game::GenerateFood()
{
	if (pFood == nullptr)
	{
		int i = 0;

		sf::Vector2u gridResolution = static_cast<sf::Vector2u>(mArenas[0].CalcTileSize());

		Position foodPosition{ rand() % gridResolution.x, rand() % gridResolution.y };
		while (IsFoodOnSnake(foodPosition) && i++ > 100)
		{
			foodPosition = Position(rand() % gridResolution.x, rand() % gridResolution.y);
		}
		
		pFood = new FoodItem(foodPosition, gridResolution);

		for (Arena& arena : mArenas)
		{
			arena.AddFood(pFood);
		}
	}
}

bool Game::IsFoodOnSnake(Position& position)
{
	for (Snake& snake : mSnakes)
	{
		Positions snakeBody = snake.GetBody();
		for (Position& snakeBodyTile : snakeBody)
		{
			if (snakeBodyTile == position)
			{
				return true;
			}
		}
	}

	return false;
}

Game::Game(sf::Vector2u windowSize)
	: pFood(nullptr)
{
	srand(time(NULL));

	InitBackground();
	InitArenas(windowSize);
	InitSnakes();
	InitGameInterface();
}

Game::~Game()
{
	if (pFood)
		delete pFood;
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

	mBackground.Draw(window);
	for (Arena & arena : mArenas)
	{
		arena.Draw(window);
	}
	mGameInterface.Draw(window);

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

	mBackground.Update();
	for (Arena & arena : mArenas)
	{
		arena.Update();
	}
	GenerateFood();
	mGameInterface.Update();
}

void Game::ProcessEvent(sf::Event e)
{
	for (auto control : mControls)
	{
		if (control == nullptr)
			continue;

		control->ProcessEvent(e);
	}
}

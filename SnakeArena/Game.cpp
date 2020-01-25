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

	Snake snake1(sf::Color(150, 50, 250), { gridTileSize.x / 2, gridTileSize.y / 2 });
	Snake snake2(sf::Color(200, 25, 180), { gridTileSize.x / 2, gridTileSize.y / 2 });

	mSnakes.push_back(snake1);
	mSnakes.push_back(snake2);

	mArenas[0].AddSnake(mSnakes[0]);
	mArenas[1].AddSnake(mSnakes[1]);

	KeyControls * key1 = new KeyControls(sf::Keyboard::Key::Up, sf::Keyboard::Key::Right, sf::Keyboard::Key::Down, sf::Keyboard::Key::Left);
	mSnakes[0].AddControl(*key1);
	mControls.push_back(key1);

	KeyControls * key2 = new KeyControls(sf::Keyboard::Key::W, sf::Keyboard::Key::D, sf::Keyboard::Key::S, sf::Keyboard::Key::A);
	mSnakes[1].AddControl(*key2);
	mControls.push_back(key2);

	/*if (sf::Joystick::isConnected(0))
	{
		GamepadControls * gamepad = new GamepadControls(0);
		mSnakes[0].AddControl(*gamepad);
		mControls.push_back(gamepad);
	}*/


	// Test
	mItems.push_back(new FoodItem(Position(80, 80), mArenas[0].CalcTileSize()));
}

void Game::InitGameInterface()
{
	mGameInterface = GameInterface();
}

Game::Game(sf::Vector2u windowSize)
{
	InitBackground();
	InitArenas(windowSize);
	InitSnakes();
	InitGameInterface();
}

Game::~Game()
{
	for (BaseItem* baseItem : mItems)
	{
		delete baseItem;
	}
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
	for (BaseItem* baseItem : mItems)
	{
		baseItem->Draw(window);
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
	for (BaseItem* baseItem : mItems)
	{
		baseItem->Update();
	}
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

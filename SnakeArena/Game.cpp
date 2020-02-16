#include <string>
#include "Game.hpp"
#include "KeyControls.hpp"
#include "GamepadControls.hpp"

const std::string Game::GameFont = "Anyfreak.ttf";

void Game::InitBackground()
{
	mBackground = Background();
}

void Game::InitArenas(sf::Vector2u windowSize)
{
	sf::Vector2u arenaSizePx = { (windowSize.x / 2), windowSize.y - HUD::Height };
	sf::Vector2u arenaResolution = { 20, 20 };
	sf::Vector2f arenaGridTileSize = { (float)arenaSizePx.x / arenaResolution.x, (float)arenaSizePx.y / arenaResolution.y };
	
	Arena arena1(arenaSizePx, arenaGridTileSize, sf::Vector2u(0, 0));
	Arena arena2(arenaSizePx, arenaGridTileSize, sf::Vector2u((windowSize.x / 2), 0));

	mArenas.push_back(arena1);
	mArenas.push_back(arena2);
}

void Game::InitSnakes()
{
	if (mArenas.size() == 0)
		return;

	auto gridResolution = mArenas[0].GetGridResolution();
	
	Snake snake1(sf::Color(150, 50, 250), { gridResolution.x / 2, gridResolution.y / 2 }, mArenas[0].GetGridTileSize());
	Snake snake2(sf::Color(200, 25, 180), { gridResolution.x / 2, gridResolution.y / 2 }, mArenas[1].GetGridTileSize());

	mSnakes.push_back(snake1);
	mSnakes.push_back(snake2);

	// Snakes
	mArenas[0].AddSnake(mSnakes[0]);
	mArenas[1].AddSnake(mSnakes[1]);

	// Shadows
	mArenas[0].AddShadow(mSnakes[1]);
	mArenas[1].AddShadow(mSnakes[0]);

	// Controls
	KeyControls * key1 = new KeyControls(sf::Keyboard::Key::W, sf::Keyboard::Key::D, sf::Keyboard::Key::S, sf::Keyboard::Key::A, sf::Keyboard::Key::E);
	mSnakes[0].AddControl(*key1);
	mControls.push_back(key1);
	
	KeyControls * key2 = new KeyControls(sf::Keyboard::Key::Up, sf::Keyboard::Key::Right, sf::Keyboard::Key::Down, sf::Keyboard::Key::Left, sf::Keyboard::Key::Space);
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
	for (int i = 0; i < mSnakes.size(); i++)
	{
		mHud.AddSnake(mSnakes[i]);
	}
}

void Game::GenerateFood()
{
	if (pFood == nullptr)
	{
		int i = 0;

		sf::Vector2u gridResolution = mArenas[0].GetGridResolution();

		Position foodPosition{ rand() % gridResolution.x, rand() % gridResolution.y };
		while (IsFoodOnSnake(foodPosition) && i++ < 100)
		{
			foodPosition = Position(rand() % gridResolution.x, rand() % gridResolution.y);
		}
		
		pFood = new FoodItem(foodPosition, mArenas[0].GetGridTileSize());

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
	, mUpdateId(0)
{
	srand(time(NULL));

	mRun = true;
	mSnakeWinner = -1;

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
	if (mArenas.size() == 0)
		return;

	mBackground.Draw(window);
	for (Arena & arena : mArenas)
	{
		arena.Draw(window);
	}
	mHud.Draw(window, {});

	if (!mRun)
		DrawEnd(window);
}

void Game::Update()
{
	// Clock
	sf::Time elapsed = mClockUpdate.getElapsedTime();
	if (elapsed.asMilliseconds() < mSpeed)
		return;
	mClockUpdate.restart();

	// Collisions
	for (int i = 0; i < mSnakes.size(); i++)
	{
		Snake& s = mSnakes[i];
		Arena& a = mArenas[i];
		if (s.ShouldUpdate(mUpdateId)
			&& (CheckSnakeBodyColision(s.GetBody(), s.GetNext()) ||
			CheckSnakeArenaColision(s.GetNext(), a.GetGridResolution())))
		{
			mSnakeWinner = i;
			PrepareEnd();
		}
	}

	// Food
	if (pFood != nullptr)
	{
		Snake* snakeEat = nullptr;
		for (Snake& snake : mSnakes)
		{
			if (snake.ShouldUpdate(mUpdateId) && snake.GetNext() == pFood->GetPosition())
			{
				if (snakeEat != nullptr)
				{
					snakeEat = nullptr;
					delete pFood;
					pFood = nullptr;
					break;
				}
				else
				{
					snakeEat = &snake;
				}
			}
		}

		if (snakeEat)
		{
			pFood->Eat(*snakeEat);
			delete pFood;
			pFood = nullptr;
		}
	}

	if (!mRun)
		return;

	UpdateMovement();
	GenerateFood();

	mUpdateId++;
}

void Game::UpdateMovement()
{
	if (mArenas.size() == 0)
		return;

	mBackground.Update();
	for (Arena & arena : mArenas)
	{
		arena.Update(mUpdateId);
	}

	mHud.Update();
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

bool Game::CheckSnakeArenaColision(const Position nextPosition, sf::Vector2u gridSize)
{
	const Position head = nextPosition;
	if (head.x < 0 || head.y < 0)
		return true;

	if (head.x >= gridSize.x ||
		head.y >= gridSize.y)
		return true;

	return false;
}

bool Game::CheckSnakeBodyColision(Positions const & snakeBody, const Position nextPosition)
{
	const Position head = nextPosition;
	for (int i = 0; i < snakeBody.size() - 1; i++)
	{
		if (head == snakeBody[i])
			return true;
	}
	return false;
}

void Game::PrepareEnd()
{
	mRun = false;
}

void Game::DrawEnd(sf::RenderWindow & window)
{
	if (mSnakeWinner < 0)
		return;

	auto wSize = window.getSize();

	sf::Font font;
	font.loadFromFile(GameFont);
	sf::Text text;
	sf::String s = "The End";
	text.setString(s);
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(mSnakes[mSnakeWinner].GetColor());
	text.setPosition((wSize.x / 2) - 80, (wSize.y / 2) - 35);

	sf::RectangleShape endBack;
	sf::Color c;
	c = sf::Color::Black;
	c.a = 240;
	endBack.setFillColor(c);
	endBack.setSize({200, 80});
	endBack.setPosition((wSize.x / 2) - (endBack.getSize().x / 2), (wSize.y / 2) - (endBack.getSize().y / 2));

	window.draw(endBack);
	window.draw(text);

}
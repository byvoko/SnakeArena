#include "Game.hpp"

#include <string>
#include <iostream>

#include "KeyControls.hpp"
#include "GamepadControls.hpp"
#include "SnakeFactory.hpp"
#include "ArenaFactory.hpp"

const std::string Game::GameFont = "Anyfreak.ttf";

void Game::InitBackground()
{
}

void Game::InitSnakes()
{
	SnakeFactory snakeFactory = SnakeFactory();
	mSnakes = *snakeFactory.CreateSnakes(4);

	// Controls
	std::list<IControls*> keyControls = std::list<IControls*>();
	keyControls.push_back(new KeyControls(sf::Keyboard::Key::W, sf::Keyboard::Key::D, sf::Keyboard::Key::S, sf::Keyboard::Key::A, sf::Keyboard::Key::E));
	keyControls.push_back(new KeyControls(sf::Keyboard::Key::Up, sf::Keyboard::Key::Right, sf::Keyboard::Key::Down, sf::Keyboard::Key::Left, sf::Keyboard::Key::Space));
	if (sf::Joystick::isConnected(0))
	{
		keyControls.push_back(new GamepadControls(0, 0));
	}
	if (sf::Joystick::isConnected(1))
	{
		keyControls.push_back(new GamepadControls(1, 0));
	}

	// If one player - use arrows
	if (mSnakes.size() == 1)
	{
		std::list<IControls*>::iterator it = keyControls.begin();
		std::advance(it, 1);

		mSnakes.front().AddControl(**it);
		mControls.push_back(*it);
	}
	else
	{
		for (std::pair<std::list<Snake>::iterator, std::list<IControls*>::iterator> it(mSnakes.begin(), keyControls.begin()); it.first != mSnakes.end() && it.second != keyControls.end(); it.first++, it.second++)
		{
			it.first->AddControl(**it.second);
			mControls.push_back(*it.second);
		}
	}
}

void Game::InitArenas(sf::Vector2u windowSize)
{
	ArenaFactory arenaFactory = ArenaFactory();
	mArenas = *arenaFactory.CreateArenas(mSnakes, { 20, 20 }, windowSize);
}

void Game::InitGameInterface()
{
}

void Game::GenerateFood()
{
	if (pFood == nullptr)
	{
		if (--nextSpeedAcumulator == 0 && mSpeed > 5)
		{
			mSpeed--;
			nextSpeedAcumulator = FoodLevelingScale;
			std::cout << "Speed up: " << mSpeed << std::endl;
		}
		int i = 0;

		sf::Vector2u gridResolution = mArenas.front().GetGridResolution();

		Position foodPosition{ rand() % gridResolution.x, rand() % gridResolution.y };
		while (IsFoodOnSnake(foodPosition) && i++ < 100)
		{
			foodPosition = Position(rand() % gridResolution.x, rand() % gridResolution.y);
		}
		
		pFood = new FoodItem(foodPosition, mArenas.front().GetGridTileSize());

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
	, mClockDraw()
	, mClockUpdate()
	, pSnakeWinner(nullptr)
	, mGameStartCountdown(3)
{
	srand(time(NULL));
	nextSpeedAcumulator = FoodLevelingScale;
	mRun = true;

	InitBackground();
	InitSnakes();
	InitArenas(windowSize);
	InitGameInterface();

	mClockDraw.restart();
	mClockUpdate.restart();
}

Game::~Game()
{
	if (pFood != nullptr)
	{
		delete pFood;
		pFood = nullptr;
	}
}

void Game::Update()
{
	// Clock
	sf::Time elapsed = mClockUpdate.getElapsedTime();
	if (elapsed.asMilliseconds() < mSpeed)
		return;
	mClockUpdate.restart();

	// Start countdown
	if (mGameStartCountdown.IsActive())
	{
		mGameStartCountdown.Update();
		return;
	}

	// Collisions
	for (std::pair<std::list<Snake>::iterator, std::list<Arena>::iterator> it(mSnakes.begin(), mArenas.begin()); it.first != mSnakes.end() & it.second != mArenas.end(); it.first++, it.second++)
	{
		if (it.first->ShouldUpdate(mUpdateId)
			&& (CheckSnakeBodyColision(it.first->GetBody(), it.first->GetNext()) ||
				CheckSnakeArenaColision(it.first->GetNext(), it.second->GetGridResolution())))
		{
			pSnakeWinner = &(*it.first);
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

	for (Arena& arena : mArenas)
	{
		arena.Update(mUpdateId);
	}
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

void Game::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	// Clock
	sf::Time elapsed = mClockDraw.getElapsedTime();
	if (elapsed.asMilliseconds() < FrameTimeMs)
		return;
	mClockDraw.restart();

	// Frame counter
	static uint64_t frameCount = 0;
	static double totalTime = 0.0;

	totalTime += elapsed.asSeconds();
	frameCount++;
	if (totalTime > 1.0)
	{
		double fps = frameCount / totalTime;

		char buffer[512];
		sprintf_s(buffer, "FPS: %f", fps);
		std::cout << buffer << std::endl;

		frameCount = 0;
		totalTime = 0.0;
	}
	// /Frame counter

	if (mArenas.size() == 0)
		return;

	window.clear();
	for (Arena& arena : mArenas)
	{
		arena.Draw(window);
	}
	//mHud.Draw(window);

	mGameStartCountdown.Draw(window);

	if (!mRun)
		DrawEnd(window);


	window.display();
}

sf::Time Game::GetSleepTime()
{
	int timeToNextUpdate = mSpeed - mClockUpdate.getElapsedTime().asMilliseconds();
	int timeToNextDraw = FrameTimeMs - mClockDraw.getElapsedTime().asMilliseconds();

	return sf::milliseconds(std::min(timeToNextUpdate, timeToNextDraw));
}

void Game::Resize(sf::Vector2u windowSize)
{
	if (mArenas.size() == 0)
		return;

	ArenaFactory af = ArenaFactory();
	af.RecalculateArenas(mArenas, windowSize);

	sf::Vector2f gridTileSize = mArenas.front().GetGridTileSize();

	for (Snake& s : mSnakes)
	{
		s.SetTileSize(gridTileSize);
	}

	if (pFood != nullptr)
	{
		pFood->SetTileSize(gridTileSize);
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
	if (pSnakeWinner == nullptr)
		return;

	auto wSize = window.getSize();

	sf::Font font;
	font.loadFromFile(GameFont);
	sf::Text text;
	sf::String s = "The End";
	text.setString(s);
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(pSnakeWinner->GetColor());
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

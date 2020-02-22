#include "SnakesFactory.hpp"

const Color SnakesFactory::SnakeColors[] = { Color(150, 50, 250),
											 Color(200, 25, 180),
											 Color(0, 0, 0),
											 Color(0, 0, 0) };

SnakesFactory::SnakesFactory()
{
}

std::list<Snake> SnakesFactory::GetSnakes(const int snakeCount)
{
	std::list<Snake> snakes = std::list<Snake>();

	for (int i = 0; i < snakeCount; i++)
	{
		snakes.push_back(Snake(SnakeColors[i]));
	}

	return snakes;
}

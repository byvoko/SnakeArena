#include "SnakeFactory.hpp"

const Color SnakeFactory::SnakeColors[] = { Color(150, 50, 250),
											 Color(200, 25, 180),
											 Color(100, 180, 30),
											 Color(30, 100, 200) };

SnakeFactory::SnakeFactory()
{
}

std::list<Snake>* SnakeFactory::CreateSnakes(const int snakeCount)
{
	std::list<Snake>* snakes = new std::list<Snake>();

	for (int i = 0; i < snakeCount; i++)
	{
		snakes->push_back(Snake(SnakeColors[i]));
	}

	return snakes;
}

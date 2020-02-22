#pragma once

#include <list>

#include "Types.hpp"
#include "Snake.hpp"

class SnakesFactory
{
private:
	static const Color SnakeColors[4];

public:
	SnakesFactory();

	std::list<Snake> GetSnakes(const int snakeCount);
};

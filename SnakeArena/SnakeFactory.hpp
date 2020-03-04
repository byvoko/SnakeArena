#pragma once

#include <list>

#include "Types.hpp"
#include "Snake.hpp"

class SnakeFactory
{
private:
	static const Color SnakeColors[4];

public:
	SnakeFactory();

	std::list<Snake>* CreateSnakes(const int snakeCount);
};

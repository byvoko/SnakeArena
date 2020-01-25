#pragma once

#include <vector>

#include "Arena.hpp"

class Game
{
private:
	std::vector<Arena&> mArenas;

public:
	Game();
	virtual ~Game();
};

#pragma once

#include "Snake.hpp"

class BaseItem
{
protected:
	Position mPosition;

public:
	BaseItem(Position position) : mPosition(position)
	{
	}

	virtual void Eat(Snake& snake) = 0;

	virtual void Draw(sf::RenderWindow & window) = 0;
	virtual void Update() = 0;
};


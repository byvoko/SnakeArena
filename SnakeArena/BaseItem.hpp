#pragma once

#include "Snake.hpp"
#include "IGameDrawable.hpp"

class BaseItem : public IGameDrawable
{
protected:
	Position mPosition;

public:
	BaseItem(Position position) : mPosition(position)
	{
	}

	virtual void Eat(Snake& snake) = 0;
	
	virtual void Update() = 0;
};


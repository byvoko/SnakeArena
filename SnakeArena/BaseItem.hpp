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

	virtual Position GetPosition()
	{
		return mPosition;
	}

	virtual void Eat(Snake& snake) = 0;
	
	virtual void Update() = 0;
};


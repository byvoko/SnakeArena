#pragma once
#include <SFML/Graphics.hpp>

#include "Types.hpp"

class ISnakeControls
{
public:
	Event UpEvent;
	Event RightEvent;
	Event DownEvent;
	Event LeftEvent;
	Event NitroEventPush;
	Event NitroEventPull;
};


class IGameControls
{
public:
	virtual void ProcessEvent(sf::Event e) = 0;
};
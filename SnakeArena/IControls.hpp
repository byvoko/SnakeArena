#pragma once
#include <functional>
#include <SFML/Graphics.hpp>

class ISnakeControls
{
public:
	std::function<void()> UpEvent;
	std::function<void()> RightEvent;
	std::function<void()> DownEvent;
	std::function<void()> LeftEvent;
	std::function<void()> NitroEvent;
};


class IGameControls
{
public:
	virtual void ProcessEvent(sf::Event e) = 0;
};
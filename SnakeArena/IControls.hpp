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
	std::function<void()> NitroEventPush;
	std::function<void()> NitroEventPull;
};


class IGameControls
{
public:
	virtual void ProcessEvent(sf::Event e) = 0;
};

class IControls : public ISnakeControls, public IGameControls
{
};

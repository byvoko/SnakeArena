#pragma once

#include <list>

#include "Snake.hpp"
#include "Arena.hpp"

class ArenaFactory
{
private:
	enum class ArenasLayout
	{
		Horizontal,
		Vertical,
		Checker
	};

	std::pair<ArenasLayout, uint32_t> GetLayoutAndGridTileSizePx(const uint32_t arenaCount, const sf::Vector2u& arenaResolution, const sf::Vector2u& windowSize);
	std::pair<sf::Vector2u, sf::Vector2u> GetArenaPositionAndIncrement(const ArenasLayout layout, const uint32_t arenaCount, const sf::Vector2u& arenaSizePx, const uint32_t gridTileSidePx, const sf::Vector2u& windowSize);
	void UpdateArenaPosition(sf::Vector2u& arenaPosition, const ArenaFactory::ArenasLayout layout, const uint32_t arenaIndex, const sf::Vector2u& arenaPositionIncrement);

public:
	ArenaFactory();

	std::list<Arena>* CreateArenas(std::list<Snake>& snakes, sf::Vector2u arenaResolution, sf::Vector2u windowSize);
	void RecalculateArenas(std::list<Arena>& arenas, sf::Vector2u windowSize);
};

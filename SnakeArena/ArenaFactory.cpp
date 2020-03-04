#include "ArenaFactory.hpp"


std::pair<ArenaFactory::ArenasLayout, uint32_t> ArenaFactory::GetLayoutAndGridTileSizePx(const uint32_t arenaCount, const sf::Vector2u& arenaResolution, const sf::Vector2u& windowSize)
{
	// All Horizontal
	ArenasLayout layout = ArenasLayout::Horizontal;
	uint32_t gridTileSidePx = (float)windowSize.y / arenaResolution.y;
	if (gridTileSidePx * arenaResolution.x * arenaCount > windowSize.x)
	{
		gridTileSidePx = windowSize.x / (arenaResolution.x * arenaCount);
	}

	// All Vertical
	uint32_t gridTileSideVerticalPx = (float)windowSize.x / arenaResolution.x;
	if (gridTileSideVerticalPx * arenaResolution.y * arenaCount > windowSize.y)
	{
		gridTileSideVerticalPx = windowSize.y / (arenaResolution.y * arenaCount);
	}
	if (gridTileSidePx < gridTileSideVerticalPx)
	{
		layout = ArenasLayout::Vertical;
		gridTileSidePx = gridTileSideVerticalPx;
	}

	// Checker
	if (arenaCount > 2)
	{
		uint32_t gridTileSideCheckerPx = (float)windowSize.x / (arenaResolution.x * 2);
		if (gridTileSideCheckerPx * arenaResolution.y * arenaCount > windowSize.y)
		{
			gridTileSideCheckerPx = windowSize.y / (arenaResolution.y * 2);
		}
		if (gridTileSidePx < gridTileSideCheckerPx)
		{
			layout = ArenasLayout::Checker;
			gridTileSidePx = gridTileSideCheckerPx;
		}
	}

	return std::pair<ArenasLayout, uint32_t>(layout, gridTileSidePx);
}

std::pair<sf::Vector2u, sf::Vector2u> ArenaFactory::GetArenaPositionAndIncrement(const ArenaFactory::ArenasLayout layout, const uint32_t arenaCount, const sf::Vector2u& arenaSizePx, const sf::Vector2u& windowSize)
{
	sf::Vector2u arenaPosition;
	sf::Vector2u arenaPositionIncrement;
	switch (layout)
	{
	case ArenaFactory::ArenasLayout::Horizontal:
		arenaPosition = sf::Vector2u((windowSize.x - arenaCount * arenaSizePx.x) / 2, (windowSize.y - arenaSizePx.y) / 2);
		arenaPositionIncrement = sf::Vector2u(arenaSizePx.x, 0);
		break;
	case ArenaFactory::ArenasLayout::Vertical:
		arenaPosition = sf::Vector2u((windowSize.x - arenaSizePx.x) / 2, (windowSize.y - arenaCount * arenaSizePx.y) / 2);
		arenaPositionIncrement = sf::Vector2u(0, arenaSizePx.y);
		break;
	case ArenaFactory::ArenasLayout::Checker:
		arenaPosition = sf::Vector2u((windowSize.x - 2 * arenaSizePx.x) / 2, (windowSize.y - 2 * arenaSizePx.y) / 2);
		arenaPositionIncrement = sf::Vector2u(arenaSizePx.x, arenaSizePx.y);
		break;
	}

	return std::pair<sf::Vector2u, sf::Vector2u>(arenaPosition, arenaPositionIncrement);
}

void ArenaFactory::UpdateArenaPosition(sf::Vector2u& arenaPosition, const ArenaFactory::ArenasLayout layout, const uint32_t arenaIndex, const sf::Vector2u& arenaPositionIncrement)
{
	switch (layout)
	{
	case ArenaFactory::ArenasLayout::Horizontal:
	case ArenaFactory::ArenasLayout::Vertical:
		arenaPosition.x += arenaPositionIncrement.x;
		arenaPosition.y += arenaPositionIncrement.y;
		break;
	case ArenaFactory::ArenasLayout::Checker:
		if (arenaIndex % 2 == 0)
		{
			arenaPosition.x += arenaPositionIncrement.x;
		}
		else
		{
			arenaPosition.x -= arenaPositionIncrement.x;
		}
		if (arenaIndex % 4 == 1)
		{
			arenaPosition.y += arenaPositionIncrement.y;
		}
		break;
	}
}

ArenaFactory::ArenaFactory()
{
}

std::list<Arena>* ArenaFactory::CreateArenas(std::list<Snake>& snakes, sf::Vector2u arenaResolution, sf::Vector2u windowSize)
{
	std::list<Arena>* arenas = new std::list<Arena>();
	size_t snakeCount = snakes.size();

	if (snakeCount == 0)
		return arenas;

	//// TODO: Every arena needs its own HUD

	std::pair<ArenasLayout, uint32_t> layoutAndGridTileSizePx = GetLayoutAndGridTileSizePx(snakeCount, arenaResolution, windowSize);
	ArenasLayout layout = layoutAndGridTileSizePx.first;
	uint32_t gridTileSidePx = layoutAndGridTileSizePx.second;

	sf::Vector2u arenaSizePx = { arenaResolution.x * gridTileSidePx, arenaResolution.y * gridTileSidePx };

	std::pair<sf::Vector2u, sf::Vector2u> arenaPositionAndIncrement = GetArenaPositionAndIncrement(layout, snakeCount, arenaSizePx, windowSize);
	sf::Vector2u arenaPosition = arenaPositionAndIncrement.first;
	sf::Vector2u arenaPositionIncrement = arenaPositionAndIncrement.second;
	
	sf::Vector2f gridTileSize = { (float)gridTileSidePx, (float)gridTileSidePx };

	// Create arenas
	uint32_t arenaIndex = 0;
	for (Snake& s : snakes)
	{
		Arena a = Arena(arenaSizePx, gridTileSize, arenaPosition);
		arenas->push_back(a);
		arenas->back().AddSnake(s);

		s.InitSnake(a.GetGridTileSize(), { arenaResolution.x / 2, arenaResolution.y / 2 });

		UpdateArenaPosition(arenaPosition, layout, arenaIndex, arenaPositionIncrement);

		arenaIndex++;
	}

	for (Snake& s : snakes)
	{
		for (Arena& a : *arenas)
		{
			a.AddShadow(s);
		}
	}

	return arenas;
}

void ArenaFactory::RecalculateArenas(std::list<Arena>& arenas, sf::Vector2u windowSize)
{
	if (arenas.size() == 0)
		return;

	const uint32_t arenaCount = arenas.size();
	const sf::Vector2u arenaResolution = arenas.front().GetGridResolution();

	std::pair<ArenasLayout, uint32_t> layoutGridTileSizePx = GetLayoutAndGridTileSizePx(arenaCount, arenaResolution, windowSize);
	ArenasLayout layout = layoutGridTileSizePx.first;
	uint32_t gridTileSidePx = layoutGridTileSizePx.second;

	sf::Vector2u arenaSizePx = { arenaResolution.x * gridTileSidePx, arenaResolution.y * gridTileSidePx };

	std::pair<sf::Vector2u, sf::Vector2u> arenaPositionAndIncrement = GetArenaPositionAndIncrement(layout, arenaCount, arenaSizePx, windowSize);
	sf::Vector2u arenaPosition = arenaPositionAndIncrement.first;
	sf::Vector2u arenaPositionIncrement = arenaPositionAndIncrement.second;

	sf::Vector2f gridTileSize = { (float)gridTileSidePx, (float)gridTileSidePx };

	uint32_t arenaIndex = 0;
	for (Arena& a : arenas)
	{
		a.SetSize(arenaSizePx);
		a.SetGridTileSize(gridTileSize);
		a.SetPosition(arenaPosition);

		UpdateArenaPosition(arenaPosition, layout, arenaIndex, arenaPositionIncrement);

		arenaIndex++;
	}
}

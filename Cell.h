#pragma once
#include"Tile.h"


class Cell
{
private:

public:
	Tile *m_tile;

	Cell();


	void insert(Tile* tile);
};


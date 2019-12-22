#include "Cell.h"




Cell::Cell()
{
	m_tile = nullptr;
}


void Cell::insert(Tile* tile)
{

	this->m_tile = tile;
}

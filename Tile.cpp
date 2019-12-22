#include "Tile.h"





void Tile::add(Tile *other)
{
	
	this->value = this->value + other->value;
	

}

bool Tile::equals(Tile* other)
{

	if (this->value == other->value ) {
		return  true;
	}
	else {
		return false;
	}

}

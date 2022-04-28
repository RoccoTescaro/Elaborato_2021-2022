#include "../headers/Tile.h"


bool Tile::isSolid()
	{
		return this->solid;
	}

void Tile::setSolid(bool solid)
	{
		this->solid = solid;
	}
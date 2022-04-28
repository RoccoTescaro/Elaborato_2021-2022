#include "Entity.h"

class Tile : public Entity {
private:
	bool solid;
public:
	bool isSolid();

/// TILE TYPES
};


class Wall : public Tile {
};
class Hole : public Tile {
};
#include "Entity.h"

class Tile : public Entity {
private:
	bool solid;
public:
	bool isSolid();

	void setSolid(bool solid);
/// TILE TYPES
};


class Wall : public Tile {
};
class Hole : public Tile {
};
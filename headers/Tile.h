#include "Entity.h"

class Tile : public Entity {
private:
	bool solid;
public:

	Tile(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim,sf::Texture &texture, bool solid): Entity(texture,cellDim), solid(solid) {
		sprite.setPosition(pos.x * cellDim.x, pos.y * cellDim.y);
		sprite.setSize(cellDim);
	}	
	bool isSolid();

/// TILE TYPES
};


class Wall : public Tile {public:
	Wall(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim, sf::Texture &texture) : Tile(pos, cellDim,texture,true) {
		sprite.setFillColor(sf::Color(255,0,0,255));
	}
	void update(const float &deltaTime) override{};
	void execute(Entity& e) override {}; 
};
class Hole : public Tile {
	public:
	Hole(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim, sf::Texture &texture) : Tile(pos, cellDim, texture, true) {
		sprite.setFillColor(sf::Color(0, 255, 0, 255));
	}

	void update(const float &deltaTime) override{};
	void execute(Entity& e) override {}; 

};
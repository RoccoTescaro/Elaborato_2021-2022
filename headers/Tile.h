#include "Entity.h"

class Tile : public Entity {
private:
	bool solid;
public:

	Tile(const sf::Color& color, sf::Vector2<int> pos, const sf::Vector2<float>& cellDim, bool solid) : Entity(color, cellDim), solid(solid) {
		sprite.setPosition(pos.x * cellDim.x, pos.y * cellDim.y );
		sprite.setSize(cellDim);
	}	
	bool isSolid();

/// TILE TYPES
};


class Wall : public Tile {
public:
	Wall(const sf::Color& color, sf::Vector2<int> pos, const sf::Vector2<float>& cellDim) : Tile(color, pos, cellDim, true) {
		sprite.setFillColor(color);
	}
	void update(const float &deltaTime) override{};
	void execute(Entity& e) override {}; 
	static Entity* deserialize(std::string string);
	std::string serialize() override;
};


/*
class Hole : public Tile {
	public:
	Hole(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim, sf::Texture &texture) : Tile(pos, cellDim, texture, true) {
		sprite.setFillColor(sf::Color(0, 255, 0, 255));
	}

	void update(const float &deltaTime) override{};
	void execute(Entity& e) override {}; 

};*/
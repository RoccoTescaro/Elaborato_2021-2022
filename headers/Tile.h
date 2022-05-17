#include "Entity.h"


#ifndef TILE_H
#define TILE_H


class Tile : public Entity {
private:
public:
	
	Tile(const sf::Color& color,sf::Vector2<int> pos, const sf::Vector2<float>& cellDim, bool solid): Entity(color,pos,cellDim,solid){
		sprite.setPosition(pos.x * cellDim.x, pos.y * cellDim.y);
		sprite.setSize(cellDim);
	}	
	std::string serialize(){
		std::string a;
		a='a';
		return a;
	};
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



class Hole : public Tile {
	public:
	bool isSolid(bool flying=false) override;
	Hole(const sf::Color& color,sf::Vector2<int> pos, const sf::Vector2<float>& cellDim) : Tile(color,pos, cellDim, true) {
		sprite.setFillColor(sf::Color(0, 255, 0, 255));
	}

	void update(const float &deltaTime) override{};
	void execute(Entity& e) override {}; 

};
#endif //TILE_H

#include "Entity.h"


#ifndef TILE_H
#define TILE_H


class Tile : public Entity {
private:
public:
	
	Tile(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim,sf::Texture &texture, bool solid): Entity(pos,texture,cellDim,solid){
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


class Wall : public Tile {public:
	Wall(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim, sf::Texture &texture) : Tile(pos, cellDim,texture,true) {
		sprite.setFillColor(sf::Color(255,0,0,255));
	}
	void update(const float &deltaTime) override{};
	void execute(Entity& e) override {}; 
};
class Hole : public Tile {
	public:
	bool isSolid(bool flying=false) override;
	Hole(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim, sf::Texture &texture) : Tile(pos, cellDim, texture, true) {
		sprite.setFillColor(sf::Color(0, 255, 0, 255));
	}

	void update(const float &deltaTime) override{};
	void execute(Entity& e) override {}; 

};



#endif //TILE_H
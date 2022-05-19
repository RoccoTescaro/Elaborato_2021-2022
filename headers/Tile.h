<<<<<<< HEAD



#ifndef TILE_H
#define TILE_H
=======
#ifndef TILES_H
#define TILES_H

>>>>>>> Map
#include "Entity.h"
#include <string>

class Tile : public Entity {
<<<<<<< HEAD
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
=======
public:
	Tile(const sf::Vector2<float>& pos, const sf::Vector2<float>& size) : Entity(pos, size) {};
protected:

>>>>>>> Map
};


class Wall : public Tile {
public:
	Wall(const sf::Vector2<float>& pos, const sf::Vector2<float>& size);

	void update(const float& dt) override {}; //#TODO
	void execute(Entity* entity) override {}; //#TODO

	std::string serialize() const override;
	static Entity* deserialize(std::string line);

	bool isSolid() const override;
private:

};

<<<<<<< HEAD


class Hole : public Tile {
	public:
	bool isSolid(bool flying=false) override;
	Hole(const sf::Color& color,sf::Vector2<int> pos, const sf::Vector2<float>& cellDim) : Tile(color,pos, cellDim, true) {
		sprite.setFillColor(sf::Color(0, 255, 0, 255));
	}
=======
class Hole : public Tile {
public:
	Hole(const sf::Vector2<float>& pos, const sf::Vector2<float>& size);
>>>>>>> Map

	void update(const float& dt) override {}; //#TODO
	void execute(Entity* entity) override {}; //#TODO

<<<<<<< HEAD
};
#endif //TILE_H
=======
	std::string serialize() const override;
	static Entity* deserialize(std::string line);

	bool isSolid() const override;
private:

};

#endif //TILES_H
>>>>>>> Map

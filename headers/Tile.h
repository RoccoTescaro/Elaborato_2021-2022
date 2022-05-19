#ifndef TILES_H
#define TILES_H

#include "Entity.h"
#include <string>

class Tile : public Entity {
public:
	Tile(const sf::Vector2<float>& pos, const sf::Vector2<float>& size) : Entity(pos, size) {};
protected:

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

class Hole : public Tile {
public:
	Hole(const sf::Vector2<float>& pos, const sf::Vector2<float>& size);

	void update(const float& dt) override {}; //#TODO
	void execute(Entity* entity) override {}; //#TODO

	std::string serialize() const override;
	static Entity* deserialize(std::string line);

	bool isSolid() const override;
private:

};

#endif //TILES_H

#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>

class Entity {
public:
	Entity(const sf::Vector2<float>& cellDim_) : cellDim(cellDim_) {}
	virtual ~Entity() {}
	void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}

	void move(const sf::Vector2<int>& pos) {
		sprite.setPosition(pos.x*cellDim.x,pos.y*cellDim.y);
	}
protected:
	const sf::Vector2<float>& cellDim; 
	sf::RectangleShape sprite;
};
class Tile : public Entity {
public:
	Tile(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim): Entity(cellDim) {
		sprite.setPosition(pos.x * cellDim.x, pos.y * cellDim.y);
		sprite.setSize(cellDim);
	}	
};
class GameCharacter : public Entity {
public:
	GameCharacter(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim) : Entity(cellDim) {
		sprite.setPosition(pos.x * cellDim.x, pos.y * cellDim.y);
		sprite.setSize(cellDim);
		sprite.setFillColor(sf::Color(0, 0, 255, 255));
	}
};
class Wall : public Tile {
public:
	Wall(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim) : Tile(pos, cellDim) {
		sprite.setFillColor(sf::Color(255,0,0,255));
	}
};
class Hole : public Tile {
public:
	Hole(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim) : Tile(pos, cellDim) {
		sprite.setFillColor(sf::Color(0, 255, 0, 255));
	}
};

class Map {
public:
	enum entityLayer { tileLayer, gameCharacterLayer, any};
	enum entityType { 
		wall = 'W',
		hole = 'H',
		empty = ' '
	};

	void load(std::fstream& file);

	void appendEntity(int x, int y, Entity* entity);

	void removeEntity(int x, int y);

	void removeEntity(int x, int y, Map::entityLayer layer);

	void render(sf::RenderWindow& window);

	void move(const sf::Vector2<int>& start, const sf::Vector2<int>& end);

	Entity* operator[](uint32_t index);
	Entity* operator[](const sf::Vector2<int>& pos);

	sf::Vector2<int> indexToPos(uint32_t index);
	uint32_t posToIndex(float x, float y);
	uint32_t posToIndex(int x, int y);
	uint32_t posToIndex(const sf::Vector2<float>& pos);
	uint32_t posToIndex(const sf::Vector2<int>& pos);

	const sf::Vector2<int>& getDim() const;

	const sf::Vector2<float>& getCellDim() const;

private:
	void appendEntity(int x, int y, char type);

	std::unordered_map<uint32_t, std::unique_ptr<Tile>> tiles;
	std::unordered_map<uint32_t, std::unique_ptr<GameCharacter>> gameCharacters;

	sf::Vector2<int> dim;
	
	const sf::Vector2<float> cellDim{ 48.f, 48.f }; //#TODO float or int
};


#endif //MAP_H
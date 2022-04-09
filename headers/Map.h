#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>

class Entity {
public:
	Entity(sf::Vector2<int> pos_) : pos(pos_) {};
	
	void render(sf::RenderWindow& window) {
		window.draw(sprite);
	};
protected:
	sf::Vector2<int> pos;
	sf::RectangleShape sprite;
};
class Tile : public Entity {
public:
	Tile(sf::Vector2<int> pos_, const sf::Vector2<float>& cellDim) : Entity(pos_) {
		sprite.setPosition(pos_.x * cellDim.x, pos_.y * cellDim.y);
		sprite.setSize(cellDim);
	}	
};
class GameCharacter : public Entity {};
class Wall : public Tile {
public:
	Wall(sf::Vector2<int> pos_, const sf::Vector2<float>& cellDim) : Tile(pos_, cellDim) {
		sprite.setFillColor(sf::Color(255,0,0,255));
	}
};
class Hole : public Tile {
public:
	Hole(sf::Vector2<int> pos_, const sf::Vector2<float>& cellDim) : Tile(pos_, cellDim) {
		sprite.setFillColor(sf::Color(0, 255, 0, 255));
	}
};

class Map {
public:
	enum entityLayer { tileLayer, gameCharacterLayer};
	enum entityType { 
		wall = 'W',
		hole = 'H',
		empty = ' '
	};

	void load(std::fstream& file);

	void appendEntity(char type, int x, int y);

	void appendEntity(GameCharacter* character, int x, int y);

	void render(sf::RenderWindow& window);

	void move(const sf::Vector2<int>& start, const sf::Vector2<int>& end);

	Entity* operator()(uint32_t pos, Map::entityLayer layer);
	Entity* operator()(float x, float y, Map::entityLayer layer);

private:
	uint32_t posToKeyConverter(uint16_t a, uint16_t b);
	uint32_t posToKeyConverter(int a, int b);
	uint32_t posToKeyConverter(float a, float b);

	std::unordered_map<uint32_t, std::shared_ptr<Tile>> tiles;
	std::unordered_map<uint32_t, std::shared_ptr<GameCharacter>> gameCharacters;

	sf::Vector2<int> dim;
	
	const sf::Vector2<float> cellDim{ 48.f, 48.f }; //#TODO float or int
};


#endif //MAP_H
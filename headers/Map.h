#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>

class Entity {};
class Tile : public Entity {};
class GameCharacter : public Entity {};

class Map {
public:
	enum entityLayer { tileLayer, gameCharacterLayer};
	enum entityType { 
		wall = 'W',
		hole = 'H',
		workingTable = 'T',
		drawable = 'D',
		npc = 'N',
		enemy = 'E',
		player = 'P'
	};

	void load(std::fstream& file);

	void appendEntity(char type, int x, int y);

	//#TODO void render();

	//#TODO void move();

	Entity* operator()(uint32_t pos, Map::entityLayer layer);
	Entity* operator()(int x, int y, Map::entityLayer layer);
	Entity* operator()(float x, float y, Map::entityLayer layer);

private:
	uint32_t posToKeyConverter(uint16_t a, uint16_t b);
	uint32_t posToKeyConverter(int a, int b);
	uint32_t posToKeyConverter(float a, float b);

	std::unordered_map<uint32_t, std::shared_ptr<Tile>> tiles;
	std::unordered_map<uint32_t, std::shared_ptr<GameCharacter>> gameCharacters;

	sf::Vector2<int> dim;
	const sf::Vector2<float> cellDim{48.f,48.f}; //#TODO float or int
};


#endif //MAP_H
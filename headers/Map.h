#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <unordered_map>
#include "Entity.h"
#include "Tile.h"
#include "GameCharacter.h"
#include "LightingSystem.h"

class Map {
public:
	enum class entityLayer { tileLayer, gameCharacterLayer, any};

	Map();
	Map(const std::string& filePath);

	void appendEntity(float x, float y, Entity* entity);
	void appendEntity(int x, int y, Entity* entity);
	void appendEntity(const sf::Vector2<float>& pos, Entity* entity);
	void appendEntity(const sf::Vector2<int>& pos, Entity* entity);

	void removeEntity(float x, float y, Map::entityLayer layer = entityLayer::any);
	void removeEntity(int x, int y, Map::entityLayer layer = entityLayer::any);
	void removeEntity(const sf::Vector2<float>& pos, Map::entityLayer layer = entityLayer::any);
	void removeEntity(const sf::Vector2<int>& pos, Map::entityLayer layer = entityLayer::any);

	Entity* operator()(float x, float y, Map::entityLayer layer = entityLayer::any) const; //getEntity with any as layer prioritize gameCharacter
	Entity* operator()(int x, int y, Map::entityLayer layer = entityLayer::any) const;
	Entity* operator()(const sf::Vector2<float>& pos, Map::entityLayer layer = entityLayer::any) const;
	Entity* operator()(const sf::Vector2<int>& pos, Map::entityLayer layer = entityLayer::any) const;
	Entity* getEntity(float x, float y, Map::entityLayer layer = entityLayer::any) const;
	Entity* getEntity(int x, int y, Map::entityLayer layer = entityLayer::any) const;
	Entity* getEntity(const sf::Vector2<float>& pos, Map::entityLayer layer = entityLayer::any) const;
	Entity* getEntity(const sf::Vector2<int>& pos, Map::entityLayer layer = entityLayer::any) const;

	sf::Vector2<int> indexToPos(uint32_t index) const;
	uint32_t posToIndex(float x, float y) const;
	uint32_t posToIndex(int x, int y) const;
	uint32_t posToIndex(const sf::Vector2<float>& pos) const;
	uint32_t posToIndex(const sf::Vector2<int>& pos) const;

	void load(const std::string& filePath); 
	void save(const std::string& filePath) const; 

	void render(sf::RenderWindow& window);

	void move(const sf::Vector2<int>& start, const sf::Vector2<int>& end); //only for GameCharacters
	bool isOccupied(float x, float y, Map::entityLayer layer, bool solid = true) const;
	bool isOccupied(int x, int y, Map::entityLayer layer, bool solid = true) const;
	bool isOccupied(const sf::Vector2<float>& pos, Map::entityLayer layer, bool solid = true) const;
	bool isOccupied(const sf::Vector2<int>& pos, Map::entityLayer layer, bool solid = true) const;

	const sf::Vector2<int>& getDim() const;
	const sf::Vector2<float>& getCellDim() const;

	const std::unordered_map<uint32_t, std::unique_ptr<Tile>>& getTileMap() const;
	const std::unordered_map<uint32_t, std::unique_ptr<GameCharacter>>& getGameCharacterMap() const;
private:
	void appendEntity(uint32_t index, Entity* entity);
	void removeEntity(uint32_t index, Map::entityLayer layer = entityLayer::any);
	Entity* getEntity(uint32_t index, Map::entityLayer layer = entityLayer::any) const;
	
	bool isOccupied(uint32_t index, Map::entityLayer layer, bool solid = true) const;
	
	std::unordered_map<std::string, Entity* (*)(std::string)> registedType;

	std::unordered_map<uint32_t, std::unique_ptr<Tile>> tiles;
	std::unordered_map<uint32_t, std::unique_ptr<GameCharacter>> gameCharacters;

	sf::Vector2<int> dim;
	const sf::Vector2<float> cellDim{ 48.f, 48.f };
	
	LightingSystem lightingSystem;
};



#endif //MAP_H
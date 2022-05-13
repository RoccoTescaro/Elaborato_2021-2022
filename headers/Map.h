#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <unordered_map>
#include "Entity.h"
#include "Tile.h"
#include "GameCharacter.h"

class Map {
public:
	enum class entityLayer { tileLayer, gameCharacterLayer, any};

	void appendEntity(float x, float y, Entity* entity); // not really wanna use template but i could
	void appendEntity(int x, int y, Entity* entity);
	void appendEntity(const sf::Vector2<float>& pos, Entity* entity);
	void appendEntity(const sf::Vector2<int>& pos, Entity* entity);

	void removeEntity(float x, float y, Map::entityLayer layer = entityLayer::any);
	void removeEntity(int x, int y, Map::entityLayer layer = entityLayer::any);
	void removeEntity(const sf::Vector2<float>& pos, Map::entityLayer layer = entityLayer::any);
	void removeEntity(const sf::Vector2<int>& pos, Map::entityLayer layer = entityLayer::any);

	Entity* operator()(float x, float y, Map::entityLayer layer = entityLayer::any); //getEntity with any as layer prioritize gameCharacter
	Entity* operator()(int x, int y, Map::entityLayer layer = entityLayer::any);
	Entity* operator()(const sf::Vector2<float>& pos, Map::entityLayer layer = entityLayer::any);
	Entity* operator()(const sf::Vector2<int>& pos, Map::entityLayer layer = entityLayer::any);
	Entity* getEntity(float x, float y, Map::entityLayer layer = entityLayer::any);
	Entity* getEntity(int x, int y, Map::entityLayer layer = entityLayer::any);
	Entity* getEntity(const sf::Vector2<float>& pos, Map::entityLayer layer = entityLayer::any);
	Entity* getEntity(const sf::Vector2<int>& pos, Map::entityLayer layer = entityLayer::any);

	sf::Vector2<int> indexToPos(uint32_t index);
	uint32_t posToIndex(float x, float y);
	uint32_t posToIndex(int x, int y);
	uint32_t posToIndex(const sf::Vector2<float>& pos);
	uint32_t posToIndex(const sf::Vector2<int>& pos);

	void load(const std::string& filePath); 
	void save(const std::string& filePath) const; 

	void render(sf::RenderWindow& window);

	void move(const sf::Vector2<int>& start, const sf::Vector2<int>& end); //only for GameCharacters

	const sf::Vector2<int>& getDim() const;
	const sf::Vector2<float>& getCellDim() const;

	template<typename T> static void registerType();
private:
	void appendEntity(uint32_t index, Entity* entity);
	void removeEntity(uint32_t index, Map::entityLayer layer = entityLayer::any);
	Entity* getEntity(uint32_t index, Map::entityLayer layer = entityLayer::any);
	
	static std::unordered_map<const char*, Entity* (*)(const std::string&)>* getRegister();

	std::unordered_map<uint32_t, std::unique_ptr<Tile>> tiles;
	std::unordered_map<uint32_t, std::unique_ptr<GameCharacter>> gameCharacters;

	sf::Vector2<int> dim;
	const sf::Vector2<float> cellDim{ 48.f, 48.f }; //#TODO float or int?
};

/*
template<typename T>
void Map::registerType() {
	getRegister()->insert(std::make_pair(typeid(T).name(),&T.deserialize)); //#TODO test T.deserialize
}*/



#endif //MAP_H
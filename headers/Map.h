#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <unordered_map>
#include "Entity.h"
#include "Tile.h"
#include "GameCharacter.h"
#include "LightingSystem.h"
#include "Log.h"


class Map {
public:
	Map();
	Map(const std::string& filePath);

	void load(const std::string& filePath);
	void save(const std::string& filePath) const;

	void render(sf::RenderWindow& window) const;

	template<class Type> 
	void append(const sf::Vector2<int>& pos, Type* entity);

	template<class Type> 
	void remove(const sf::Vector2<int>& pos);

	template<class Type> 
	Type* get(const sf::Vector2<int>& pos) const;
	template<class Player> 
	Player* get() const;

	template<class Type> 
	void move(const sf::Vector2<int>& start, const sf::Vector2<int>& end);

	template<class Type> 
	bool isOccupied(const sf::Vector2<int>& pos, bool solid = false) const;

	sf::Vector2<int> worldCoordToPos(const sf::Vector2<float>& worldCoord) const;
	sf::Vector2<float> posToWorldCoord(const sf::Vector2<int>& pos) const;

	sf::Vector2<int> getCellDim() const;
private:
	template<class Type> void record();

	struct hash {
		std::size_t operator () (const sf::Vector2<int>& pos) const {
			auto h1 = std::hash<int>{}(pos.x);
			auto h2 = std::hash<int>{}(pos.y);
			return h1 ^ h2;
		}
	};

	std::unordered_map<const char*, uint8_t> typesRegister;
	
	std::unordered_map<uint8_t, std::unordered_map<sf::Vector2<int>, std::unique_ptr<Tile>, hash>> tiles;
	std::unordered_map<uint8_t, std::unordered_map<sf::Vector2<int>, std::unique_ptr<GameCharacter>, hash>> gameCharacters;

	std::unordered_map<uint8_t, Entity* (*)(std::string)> deserializeFunctions;

	uint32_t nEntities;
	const sf::Vector2<int> cellDim{ 48, 48 };

	LightingSystem lightingSystem;
};


template<class Type>
void Map::append(const sf::Vector2<int>& pos, Type* entity) 
{
	uint8_t id = typesRegister[typeid(Type).name()]; //#TODO check with find if typeid.name() is in register							 
	Tile* tile = dynamic_cast<Tile*>(entity);
	GameCharacter* gameCharacter = dynamic_cast<GameCharacter*>(entity);

	bool occupied = tile? isOccupied<Tile>(pos, entity->isSolid()) : isOccupied<GameCharacter>(pos, entity->isSolid());
	
	if (!occupied) {
		if (tile) {
			nEntities++;
			tiles[id][pos] = static_cast<std::unique_ptr<Tile>>(tile);
			DEBUG("allocated tile at pos {%,%}", pos.x, pos.y);
		}
		else if (gameCharacter) {
			nEntities++;
			gameCharacters[id][pos] = static_cast<std::unique_ptr<GameCharacter>>(gameCharacter);
			DEBUG("allocated gamecharacter at pos {%,%}", pos.x, pos.y);
		}
		else
		{
			ERROR("attempt to allocate a non valid entity");
			delete entity;
		}
	}
	else 
		delete entity;
	
}

template<class Type>
void Map::remove(const sf::Vector2<int>& pos)
{
	uint8_t id = typesRegister[typeid(Type).name()];

	if (tiles.find(id) != tiles.end())
		tiles[id].erase(pos);
	else if (gameCharacters.find(id) != gameCharacters.end())
		gameCharacters[id].erase(pos);
	else
		ERROR("attempt to remove a non valid entity");
}

template<>
void Map::remove<Tile>(const sf::Vector2<int>& pos);

template<>
void Map::remove<GameCharacter>(const sf::Vector2<int>& pos);

template<>
void Map::remove<Entity>(const sf::Vector2<int>& pos);

template<class Type>
Type* Map::get(const sf::Vector2<int>& pos) const
{
	uint8_t id = typesRegister.at(typeid(Type).name());

	if (tiles.find(id) != tiles.end() && tiles.at(id).find(pos) != tiles.at(id).end())
		return dynamic_cast<Type*>(tiles.at(id).at(pos).get());
	else if (gameCharacters.find(id) != gameCharacters.end() && gameCharacters[id].find(pos) != gameCharacters.at(id).end())
		return dynamic_cast<Type*>(gameCharacters.at(id).at(pos).get());
	else
		return nullptr;
}

template<>
Entity* Map::get<Entity>(const sf::Vector2<int>& pos) const;

template<>
Tile* Map::get<Tile>(const sf::Vector2<int>& pos) const;

template<>
GameCharacter* Map::get<GameCharacter>(const sf::Vector2<int>& pos) const;

template<class Player>
Player* Map::get() const
{
	auto& players = gameCharacters.at(typesRegister.at(typeid(Player).name()));

	for (auto& player : players)
		return player.second.get();
}

template<class Type>
void Map::move(const sf::Vector2<int>& start, const sf::Vector2<int>& end)
{
	Type* entity = get<Type>(start);

	bool occupied;
	if (tiles.find(typesRegister[typeid(Type).id()]) != tiles.end())
		occupied = isOccupied<Tile>(end, entity->isSolid());
	else
		occupied = isOccupied<GameCharacter>(end, entity->isSolid());

	if (entity && !occupied) {
		remove<Type>(start);
		append<Type>(end, entity);
		entity->move(end);
	}
}

template<class Type>
bool Map::isOccupied(const sf::Vector2<int>& pos, bool solid) const
{
	Type* entity = get<Type>(pos);
	return entity && entity->isSolid();
}

template<>
bool Map::isOccupied<Tile>(const sf::Vector2<int>& pos, bool solid) const;

template<>
bool Map::isOccupied<GameCharacter>(const sf::Vector2<int>& pos, bool solid) const;

template <class Type>
void Map::record()
{
	static uint8_t nTypes = 0;
	typesRegister.emplace(typeid(Type).name(), nTypes);
	deserializeFunctions.emplace(nTypes, &Type::deserialize);
	nTypes++;
}

#endif //MAP_H

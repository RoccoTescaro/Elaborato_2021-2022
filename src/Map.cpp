#include "../headers/Map.h"
#include <iostream>
#include "../headers/Log.h"
#include <cmath>
#include <algorithm>

#ifndef _DEBUG 
#define BASE_WIDTH 0
#define BASE_HEIGHT 0
#else //EDITOR MODE (don't optimize space)
#define BASE_WIDTH 1024
#define BASE_HEIGHT 1024
#endif

#define REGISTER(Type) std::make_pair(#Type, &Type::deserialize)

Map::Map() {
	//TILES
	registedType.insert(REGISTER(Wall));
	registedType.insert(REGISTER(Hole));
	//GAMECHARACTERS
	registedType.insert(REGISTER(Melee));
	registedType.insert(REGISTER(Bat));
	registedType.insert(REGISTER(Ranged));
	registedType.insert(REGISTER(Player));
}

Map::Map(const std::string& filePath) : Map(){
	load(filePath);
}

void Map::appendEntity(float x, float y, Entity* entity) {
	appendEntity(posToIndex(x,y), entity);
}

void Map::appendEntity(int x, int y, Entity* entity) {
	appendEntity(posToIndex(x, y), entity);
}

void Map::appendEntity(const sf::Vector2<float>& pos, Entity* entity) {
	appendEntity(posToIndex(pos), entity);
}

void Map::appendEntity(const sf::Vector2<int>& pos, Entity* entity) {
	appendEntity(posToIndex(pos), entity);
}

void Map::appendEntity(uint32_t index, Entity* entity) {
	GameCharacter* character = dynamic_cast<GameCharacter*>(entity);
	if (character && !Map::isOccupied(index, Map::entityLayer::gameCharacterLayer, entity->isSolid())) {
		gameCharacters.emplace(index, character);
		DEBUG("GameCharacter allocated, key:{%}", index);
	}
	Tile* tile = dynamic_cast<Tile*>(entity);
	if (tile && !Map::isOccupied(index, Map::entityLayer::tileLayer, entity->isSolid())) {
		tiles.emplace(index, tile);
		DEBUG("Tile allocated, key:{%}", index);
	}
}

void Map::removeEntity(float x, float y, Map::entityLayer layer) {
	removeEntity(posToIndex(x, y), layer);
}

void Map::removeEntity(int x, int y, Map::entityLayer layer) {
	removeEntity(posToIndex(x, y), layer);
}

void Map::removeEntity(const sf::Vector2<float>& pos, Map::entityLayer layer) {
	removeEntity(posToIndex(pos), layer);
}

void Map::removeEntity(const sf::Vector2<int>& pos, Map::entityLayer layer) {
	removeEntity(posToIndex(pos), layer);
}

void Map::removeEntity(uint32_t index, Map::entityLayer layer) {
	if ((layer == Map::entityLayer::gameCharacterLayer || layer == Map::entityLayer::any) && gameCharacters.erase(index)) DEBUG("GameCharacter removed, key:{%}", index);
	if ((layer == Map::entityLayer::tileLayer || layer == Map::entityLayer::any) && tiles.erase(index)) DEBUG("Tile removed, key:{%}", index);
}

Entity* Map::operator()(float x, float y, Map::entityLayer layer) const {
	return Map::getEntity(posToIndex(x, y), layer);
}

Entity* Map::operator()(int x, int y, Map::entityLayer layer) const {
	return Map::getEntity(posToIndex(x, y), layer);
}

Entity* Map::operator()(const sf::Vector2<float>& pos, Map::entityLayer layer) const {
	return Map::getEntity(posToIndex(pos), layer);
}

Entity* Map::operator()(const sf::Vector2<int>& pos, Map::entityLayer layer) const {
	return Map::getEntity(posToIndex(pos), layer);
}

Entity* Map::getEntity(float x, float y, Map::entityLayer layer) const {
	return Map::getEntity(posToIndex(x, y), layer);
}

Entity* Map::getEntity(int x, int y, Map::entityLayer layer) const {
	return Map::getEntity(posToIndex(x, y), layer);
}

Entity* Map::getEntity(const sf::Vector2<float>& pos, Map::entityLayer layer) const {
	return Map::getEntity(posToIndex(pos), layer);
}

Entity* Map::getEntity(const sf::Vector2<int>& pos, Map::entityLayer layer) const {
	return Map::getEntity(posToIndex(pos), layer);
}

Entity* Map::getEntity(uint32_t index, Map::entityLayer layer) const {
	auto character = gameCharacters.find(index);
	if (character != gameCharacters.end() && (layer == Map::entityLayer::any || layer == Map::entityLayer::gameCharacterLayer)) return character->second.get();
	auto tile = tiles.find(index);
	if (tile != tiles.end() && (layer == Map::entityLayer::any || layer == Map::entityLayer::tileLayer)) return tile->second.get();
	return nullptr;
}

sf::Vector2<int> Map::indexToPos(uint32_t index) const {
	return sf::Vector2<int>(std::min<int>(std::max<int>(index >> 16, 0), dim.x - 1), std::min<int>(std::max<int>(index & 0x0000FFFFU, 0), dim.y - 1));
}

uint32_t  Map::posToIndex(float x, float y) const {
	x = std::min(dim.x * cellDim.x - 1.f, std::max(0.f, x));
	y = std::min(dim.y * cellDim.y - 1.f, std::max(0.f, y));
	return static_cast<uint32_t>(int(x / cellDim.x)) << 16 | static_cast<uint32_t>((int)y / cellDim.y);
}

uint32_t  Map::posToIndex(int x, int y) const {
	x = std::min(dim.x - 1, std::max(0, x));
	y = std::min(dim.y - 1, std::max(0, y));
	return static_cast<uint32_t>(x) << 16 | static_cast<uint32_t>(y);
}

uint32_t  Map::posToIndex(const sf::Vector2<float>& pos) const {
	return posToIndex(pos.x,pos.y);
}

uint32_t  Map::posToIndex(const sf::Vector2<int>& pos) const {
	return posToIndex(pos.x,pos.y);
}

void Map::load(const std::string& filePath) {
	std::fstream file;
	file.open(filePath, std::fstream::in);
	std::string line;
	dim = { BASE_WIDTH , BASE_HEIGHT };

	while (std::getline(file, line))
	{
		std::string string = line;
		uint32_t index = static_cast<uint32_t>(std::stoul(string.substr(0, string.find(" "))));
		string.erase(0, string.find(" ") + 1);

		sf::Vector2<int> pos = { index >> 16, index & 0x0000FFFFU }; //setting up map dimension 
		if (pos.x > dim.x) dim.x = pos.x+1;
		if (pos.y > dim.y) dim.y = pos.y+1;

		std::string type = string.substr(0, string.find(" "));
		string.erase(0, string.find(" ") + 1);
		auto deserialize = registedType[type];
		if (deserialize) {
			Entity* entity = deserialize(string);
			Map::appendEntity(index, entity);
		}
		else
			DEBUG("Error trying to deserialize entity. Probably loading txt file has been corrupted.");
	}
}

void Map::save(const std::string& filePath) const {
	DEBUG("Saving...");
	std::fstream file;
	file.open(filePath, std::fstream::out | std::fstream::trunc); //clear the txt file
	if (!file.is_open())
		ERROR("Can't open map file");
	for (auto i = gameCharacters.begin(); i != gameCharacters.end(); ++i)
		file << i->first << " " << i->second->serialize() << std::endl;
	for (auto i = tiles.begin(); i != tiles.end(); ++i)
		file << i->first << " " << i->second->serialize() << std::endl;
	file.close();
}

void Map::render(sf::RenderWindow& window) {
	auto& view = window.getView(); 
	for (float j = std::max<float>(view.getCenter().y - view.getSize().y*0.5f -cellDim.y, 0.f); j < std::min<float>(view.getCenter().y + view.getSize().y * 0.5 + cellDim.y,dim.y*cellDim.y); j += cellDim.y)
		for (float i = std::max<float>(view.getCenter().x - view.getSize().x * 0.5f - cellDim.x, 0.f); i < std::min<float>(view.getCenter().x + view.getSize().x * 0.5f + cellDim.x,dim.x*cellDim.y); i += cellDim.x) {
			auto tile = Map::getEntity(posToIndex(i, j));
			if (tile) tile->render(window);
			auto gameCharater = Map::getEntity(posToIndex(i,j));
			if (gameCharater) gameCharater->render(window);
		}
}

void Map::move(const sf::Vector2<int>& start, const sf::Vector2<int>& end) {
	auto startCell = Map::getEntity(start, Map::entityLayer::gameCharacterLayer);

	if (startCell && !Map::isOccupied(end,Map::entityLayer::gameCharacterLayer,startCell->isSolid())) {
		auto entity = gameCharacters.extract(posToIndex(start));
		entity.key() = posToIndex(end);
		gameCharacters.insert(std::move(entity));
		Map::getEntity(end,Map::entityLayer::gameCharacterLayer)->move(static_cast<sf::Vector2<float>>(end));
	}
}

bool  Map::isOccupied(float x, float y, Map::entityLayer layer, bool solid) const {
	return Map::isOccupied(posToIndex(x, y), layer, solid);
}

bool  Map::isOccupied(int x, int y, Map::entityLayer layer, bool solid) const {
	return Map::isOccupied(posToIndex(x, y), layer, solid);
}

bool  Map::isOccupied(const sf::Vector2<float>& pos, Map::entityLayer layer, bool solid) const {
	return Map::isOccupied(posToIndex(pos), layer, solid);
}

bool  Map::isOccupied(const sf::Vector2<int>& pos, Map::entityLayer layer, bool solid) const {
	return Map::isOccupied(posToIndex(pos), layer, solid);
}

bool Map::isOccupied(uint32_t index, Map::entityLayer layer, bool solid) const {
	auto gameCharacter = Map::getEntity(index, Map::entityLayer::gameCharacterLayer);
	auto tile = Map::getEntity(index, Map::entityLayer::tileLayer);

	switch (layer) {
		case Map::entityLayer::any:
			return gameCharacter || tile;
		case Map::entityLayer::tileLayer:
			return tile || (solid && gameCharacter) || (!solid && gameCharacter && gameCharacter->isSolid());
		case Map::entityLayer::gameCharacterLayer:
			return gameCharacter || (solid && tile) || (!solid && tile && tile->isSolid());
	}
}

const sf::Vector2<int>& Map::getDim() const {
	return dim;
}

const sf::Vector2<float>& Map::getCellDim() const{
	return cellDim;
}
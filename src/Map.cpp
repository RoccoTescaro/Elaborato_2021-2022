#include "../headers/Map.h"
#include <iostream>
#include "../headers/Log.h"
#include <cmath>

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
	if (character) {
		gameCharacters.emplace(index, character);
		DEBUG("GameCharacter allocated, key:{%}", index);
	}
	Tile* tile = dynamic_cast<Tile*>(entity);
	if (tile) {
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

Entity* Map::operator()(float x, float y, Map::entityLayer layer) {
	return Map::getEntity(posToIndex(x, y), layer);
}

Entity* Map::operator()(int x, int y, Map::entityLayer layer) {
	return Map::getEntity(posToIndex(x, y), layer);
}

Entity* Map::operator()(const sf::Vector2<float>& pos, Map::entityLayer layer) {
	return Map::getEntity(posToIndex(pos), layer);
}

Entity* Map::operator()(const sf::Vector2<int>& pos, Map::entityLayer layer) {
	return Map::getEntity(posToIndex(pos), layer);
}

Entity* Map::getEntity(float x, float y, Map::entityLayer layer) {
	return Map::getEntity(posToIndex(x, y), layer);
}

Entity* Map::getEntity(int x, int y, Map::entityLayer layer) {
	return Map::getEntity(posToIndex(x, y), layer);
}

Entity* Map::getEntity(const sf::Vector2<float>& pos, Map::entityLayer layer) {
	return Map::getEntity(posToIndex(pos), layer);
}

Entity* Map::getEntity(const sf::Vector2<int>& pos, Map::entityLayer layer) {
	return Map::getEntity(posToIndex(pos), layer);
}

Entity* Map::getEntity(uint32_t index, Map::entityLayer layer) {
	auto character = gameCharacters.find(index);
	if (character != gameCharacters.end() && (layer == Map::entityLayer::any || layer == Map::entityLayer::gameCharacterLayer)) return character->second.get();
	auto tile = tiles.find(index);
	if (tile != tiles.end() && (layer == Map::entityLayer::any || layer == Map::entityLayer::tileLayer)) return tile->second.get();
	return nullptr;
}

sf::Vector2<int> Map::indexToPos(uint32_t index) {
	return sf::Vector2<int>(std::min<int>(std::max<int>(index >> 16, 0), dim.x - 1), std::min<int>(std::max<int>(index & 0x0000FFFFU, 0), dim.y - 1));
}

uint32_t  Map::posToIndex(float x, float y) {
	return static_cast<uint32_t>(int(x / cellDim.x)) << 16 | static_cast<uint32_t>((int)y / cellDim.y);
}

uint32_t  Map::posToIndex(int x, int y) {
	return static_cast<uint32_t>(x) << 16 | static_cast<uint32_t>(y);
}

uint32_t  Map::posToIndex(const sf::Vector2<float>& pos) {
	return static_cast<uint32_t>(pos.x / cellDim.x) << 16 | static_cast<uint32_t>(pos.y / cellDim.y);
}

uint32_t  Map::posToIndex(const sf::Vector2<int>& pos) {
	return static_cast<uint32_t>(pos.x) << 16 | static_cast<uint32_t>(pos.y);
}

void Map::load(std::fstream& file) {

}

void Map::save(std::fstream& file) {

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
	const auto& startCell = dynamic_cast<GameCharacter*>(Map::getEntity(start, Map::entityLayer::gameCharacterLayer));
	const auto& endCell = dynamic_cast<GameCharacter*>(Map::getEntity(end, Map::entityLayer::gameCharacterLayer));

	if (startCell && !endCell) {
		auto entity = gameCharacters.extract(posToIndex(start));
		entity.key() = posToIndex(end);
		gameCharacters.insert(std::move(entity));
		Map::getEntity(end,Map::entityLayer::gameCharacterLayer)->move(end);
	}
}

const sf::Vector2<int>& Map::getDim() const {
	return dim;
}

const sf::Vector2<float>& Map::getCellDim() const{
	return cellDim;
}

std::unordered_map<const char*, Entity* (*)(const std::string&)>* Map::getRegister() {
	static std::unordered_map<const char*, Entity* (*)(const std::string&)>* registerType;
	if (!registerType) registerType = new std::unordered_map<const char*, Entity* (*)(const std::string&)>;
	return registerType;
}

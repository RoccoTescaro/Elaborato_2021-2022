#include "../headers/Map.h"
#include <iostream>
#include "../headers/Log.h"
#include <cmath>

void Map::load(std::fstream& file) {
	if (file.is_open()) {
		std::string firstLine;
		std::getline(file, firstLine);
		auto space = firstLine.find(' ');
		if (firstLine.size() <= 0 || space == std::string::npos) {
			ERROR("loading - map file has a wrong format");
			return;
		}
		dim = { stoi(firstLine.substr(0,space)), stoi(firstLine.substr(space+1,firstLine.size()))};
		for (int j = 0; j < dim.y; ++j) {
			std::string line;
			std::getline(file, line);
			if(line.size() <= 0) break;
			for (int i = 0; i < dim.x; ++i) {
				if (i >= line.size()) break;
				appendEntity(line[i],i,j);
			}
		}
		file.close();
	}
	else
		ERROR("loading - map file has not been open");
}

void Map::appendEntity(char type, int x, int y){
	if (x < dim.x && x >= 0 && y < dim.y && y >= 0) {
		switch (type) {
		case entityType::wall: {
			DEBUG("Wall allocated, key:{%}", posToIndex(x, y));
			tiles.emplace(posToIndex(x, y), new Wall({ x,y }, cellDim));
			break;
		}
		case entityType::hole: {
			DEBUG("Hole allocated, key:{%}", posToIndex(x, y));
			tiles.emplace(posToIndex(x, y), new Hole({ x,y }, cellDim));
			break;
		}
		case entityType::empty: {
			break;
		}
		default: {
			ERROR("trying to istanciate an unknown type");
			break;
		}
		}
	}
	else
		ERROR("trying to allocate an Entity but non map has been loaded yet");
}

void Map::appendEntity(int x, int y, Entity* entity) {
	GameCharacter* character = dynamic_cast<GameCharacter*>(entity);
	if (character) {
		gameCharacters.emplace(posToIndex(x, y),character);
		DEBUG("GameCharacter allocated, key:{%}", posToIndex(x, y));
	}
	Tile* tile = dynamic_cast<Tile*>(entity);
	if (tile) {
		tiles.emplace(posToIndex(x, y), tile);
		DEBUG("Tile allocated, key:{%}", posToIndex(x, y));
	}
}

void Map::removeEntity(int x, int y) {
	if (gameCharacters.erase(posToIndex(x, y))) DEBUG("GameCharacter removed, key:{%}", posToIndex(x, y));
	if (tiles.erase(posToIndex(x, y))) DEBUG("Tile removed, key:{%}", posToIndex(x, y));
}

void Map::removeEntity(int x, int y, Map::entityLayer layer) {
	if (layer == Map::entityLayer::gameCharacterLayer) 
		gameCharacters.erase(posToIndex(x, y));
	else if (layer == Map::entityLayer::tileLayer)
		tiles.erase(posToIndex(x, y));
}

void Map::render(sf::RenderWindow& window) {
	auto& view = window.getView(); 
	for (float j = std::max<float>(view.getCenter().y - view.getSize().y*0.5f -cellDim.y, 0.f); j < std::min<float>(view.getCenter().y + view.getSize().y * 0.5 + cellDim.y,dim.y*cellDim.y); j += cellDim.y)
		for (float i = std::max<float>(view.getCenter().x - view.getSize().x * 0.5f - cellDim.x, 0.f); i < std::min<float>(view.getCenter().x + view.getSize().x * 0.5f + cellDim.x,dim.x*cellDim.y); i += cellDim.x) {
			auto tile = Map::operator[](posToIndex(i, j));
			if (tile) tile->render(window);
			auto gameCharater = Map::operator[](posToIndex(i,j));
			if (gameCharater) gameCharater->render(window);
		}
}

void Map::move(const sf::Vector2<int>& start, const sf::Vector2<int>& end) {
	if (Map::operator[](start) && !Map::operator[](end)) {
		if (dynamic_cast<GameCharacter*>(Map::operator[](start))) {
		auto entity = gameCharacters.extract(posToIndex(start));
		entity.key() = posToIndex(end);
		gameCharacters.insert(std::move(entity));
		Map::operator[](end)->move(end);
		}
		else if (dynamic_cast<Entity*>(Map::operator[](start))) {
		auto entity = tiles.extract(posToIndex(start));
		DEBUG("Tile moved, key: {%}->{%}, pos:{%,%}->{%,%}", posToIndex(start), posToIndex(end), start.x, start.y, end.x, end.y);
		entity.key() = posToIndex(end);
		tiles.insert(std::move(entity));
		Map::operator[](end)->move(end);
		}
	}
	else
		ERROR("no Entity in starting tile");
}


Entity* Map::operator[](uint32_t index) {
	auto character = gameCharacters.find(index);
	if (character != gameCharacters.end()) return character->second.get();
	auto tile = tiles.find(index);
	if (tile != tiles.end()) return tile->second.get();
	return NULL;
}

Entity* Map::operator[](const sf::Vector2<int>& pos) {
	if (pos.x < 0 || pos.y < 0 || pos.x >= dim.x || pos.y >= dim.y) return NULL;
	return Map::operator[](posToIndex(pos));
}

sf::Vector2<int> Map::indexToPos(uint32_t index) {
	return sf::Vector2<int>(std::min<int>(std::max<int>(index >> 16,0),dim.x-1), std::min<int>(std::max<int>(index & 0x0000FFFFU, 0), dim.y - 1));
}

uint32_t  Map::posToIndex(float x, float y) {
	return static_cast<uint32_t>(int(x/cellDim.x)) << 16 | static_cast<uint32_t>((int)y/cellDim.y);
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


const sf::Vector2<int>& Map::getDim() const {
	return dim;
}

const sf::Vector2<float>& Map::getCellDim() const{
	return cellDim;
}


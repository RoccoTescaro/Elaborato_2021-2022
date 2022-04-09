#include "../headers/Map.h"
#include <iostream>
#include "../headers/Log.h"

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
			DEBUG("Wall allocated, key:{%}", posToKeyConverter(x, y));
			tiles.emplace(posToKeyConverter(x, y), new Wall({ x,y }, cellDim));
			break;
		}
		case entityType::hole: {
			DEBUG("Hole allocated, key:{%}",posToKeyConverter(x, y));
			tiles.emplace(posToKeyConverter(x, y), new Hole({ x,y }, cellDim));
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

void Map::appendEntity(GameCharacter* character, int x, int y) {
	gameCharacters.emplace(posToKeyConverter(x, y), character);
}

void Map::render(sf::RenderWindow& window) {
	auto& view = window.getView(); 
	for (float j = std::max<float>(view.getCenter().y - view.getSize().y*0.5f -cellDim.y, 0.f); j < std::min<float>(view.getCenter().y + view.getSize().y * 0.5 + cellDim.y,dim.y*cellDim.y); j += cellDim.y)
		for (float i = std::max<float>(view.getCenter().x - view.getSize().x * 0.5f - cellDim.x, 0.f); i < std::min<float>(view.getCenter().x + view.getSize().x * 0.5f + cellDim.x,dim.x*cellDim.y); i += cellDim.x) {
			auto tile = Map::operator()(i, j, Map::tileLayer);
			if (tile) tile->render(window);
			auto gameCharater = Map::operator()(i,j,Map::gameCharacterLayer);
			if (gameCharater) gameCharater->render(window);
		}
}

void Map::move(const sf::Vector2<int>& start, const sf::Vector2<int>& end) {
	if (Map::operator()(posToKeyConverter(start.x, start.y), Map::gameCharacterLayer)) { //#TODO fix conversion
		auto character = static_cast<GameCharacter*>(Map::operator()(posToKeyConverter(start.x, start.y), Map::gameCharacterLayer));
		gameCharacters.erase(posToKeyConverter(start.x, start.y));
		appendEntity(character, end.x, end.y);
	}
	else
		ERROR("no Entity in starting tile");
}


 Entity* Map::operator()(uint32_t pos, Map::entityLayer layer = gameCharacterLayer) {
	if (layer == gameCharacterLayer) {
		auto entity = gameCharacters.find(pos);
		if (entity != gameCharacters.end()) return entity->second.get();
	}
	else if (layer == tileLayer) {
		auto entity = tiles.find(pos);
		if (entity != tiles.end()) return entity->second.get();
	}
	return NULL;
}

Entity* Map::operator()(float x, float y, Map::entityLayer layer = gameCharacterLayer) {
	return Map::operator()(posToKeyConverter(x, y), layer);
}


uint32_t Map::posToKeyConverter(uint16_t a, uint16_t b) {
	return (a << 16) | b;
}

uint32_t Map::posToKeyConverter(int a, int b) {
	return posToKeyConverter(uint16_t(a), uint16_t(b));
}

uint32_t Map::posToKeyConverter(float a, float b) {
	if (a < 0 || b < 0) return 0;
	return posToKeyConverter(uint16_t(a / cellDim.x), uint16_t(b / cellDim.y));
}
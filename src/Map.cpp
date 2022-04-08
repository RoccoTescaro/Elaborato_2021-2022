#include "../headers/Map.h"
#include <iostream>

void Map::load(std::fstream& file) {
	if (file.is_open()) {
		std::string firstLine;
		std::getline(file, firstLine);
		dim = { stoi(firstLine.substr(0,firstLine.find(' '))), stoi(firstLine.substr(firstLine.find(' '),firstLine.size()))};
		for (int j = 0; j < dim.y; ++j) {
			std::string line;
			if(std::getline(file, line).eofbit) break;
			for (int i = 0; i < dim.x; ++i) {
				if (i >= line.size()) break;
				appendEntity(line[i],i,j);
			}
		}
		file.close();
	}
	else
		std::cout << "ERROR: loading-map file has not been open" << std::endl;
}

void Map::appendEntity(char type, int x, int y){
	switch (type) {
	case entityType::wall: {
		tiles.emplace(posToKeyConverter(x,y),new Tile); //WALL 
		break;
	}
	case entityType::player: {
		break;
	}
	default: {
		std::cout << "ERROR: trying to istanciate an unknown type" << std::endl;
		break;
	}
	}
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

Entity* Map::operator()(int x, int y, Map::entityLayer layer = gameCharacterLayer) {
	return Map::operator()(posToKeyConverter(x,y), layer);
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
	return posToKeyConverter(uint16_t(uint16_t(a / cellDim.x) * cellDim.x),
							 uint16_t(uint16_t(a / cellDim.y) * cellDim.y));
}
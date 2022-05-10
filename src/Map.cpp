#include "../headers/Map.h"
#include <iostream>
#include "../headers/Log.h"
#include <cmath>

<<<<<<< HEAD
void Map::load(std::fstream& file) {
	sf::Texture *t1;
	t1=new(sf::Texture);
	if (!(*t1).loadFromFile("../images/texture/Enemy.png"))
        {
                 // error...
        }
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

				appendEntity(i,j,line[i],*t1);
			}
		}
		file.close();
	}
	else
		ERROR("loading - map file has not been open");
=======
void Map::appendEntity(float x, float y, Entity* entity) {
	appendEntity(posToIndex(x,y), entity);
>>>>>>> Map
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

void Map::load(const std::string& filePath) {
	std::fstream file;
	file.open(filePath, std::fstream::in);
	std::string line;
	dim = { 0 , 0 };

	while (std::getline(file, line))
	{
		uint32_t index = static_cast<uint32_t>(std::stoul(line.substr(0, line.find(" "))));
		auto entity = (* Map::getRegister())[line.substr(line.find(" ") + 1, line.substr(line.find(" ")+1,line.size()).find(" ")).c_str()](line.substr(line.find(" ")+1,line.size()));
		Map::appendEntity(index, entity);

		auto pos = indexToPos(index); //setting up map dimension 
		if (pos.x > dim.x) dim.x = pos.x;
		if (pos.y > dim.y) dim.y = pos.y;
	}
}

void Map::save(const std::string& filePath) const {
	std::fstream file;
	file.open(filePath, std::fstream::out | std::fstream::trunc); //clear the txt file
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
	auto endCell = Map::getEntity(end, Map::entityLayer::gameCharacterLayer);

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

<<<<<<< HEAD
void Map::appendEntity(int x, int y, char type,sf::Texture &texture){ //cannot cast char to enum value but we can compare it.
	if (x < dim.x && x >= 0 && y < dim.y && y >= 0) {
		switch (type) {
		case entityType::wall: {
			DEBUG("Wall allocated, key:{%}", posToIndex(x, y));
			tiles.emplace(posToIndex(x, y), new Wall({ x,y }, cellDim,texture));
			break;
		}
		case entityType::hole: {
			DEBUG("Hole allocated, key:{%}", posToIndex(x, y));
			tiles.emplace(posToIndex(x, y), new Hole({ x,y }, cellDim,texture));
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
=======
std::unordered_map<const char*, Entity* (*)(const std::string&)>* Map::getRegister() {
	static std::unordered_map<const char*, Entity* (*)(const std::string&)>* registerType;
	if (!registerType) registerType = new std::unordered_map<const char*, Entity* (*)(const std::string&)>;
	return registerType;
>>>>>>> Map
}

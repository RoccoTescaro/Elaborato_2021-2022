#include "../headers/Map.h"
#include <iostream>
#include "../headers/Log.h"
#include <cmath>
#include <algorithm>

Map::Map() {
	//TILES
	record<Wall>();
	record<Hole>();
	//GAMECHARACTERS
	record<Melee>();
	record<Bat>();
	record<Ranged>();
	record<Player>();
}

Map::Map(const std::string& filePath) : Map() {
	load(filePath);
}


void Map::load(const std::string& filePath) { //#TODO fix me
	std::fstream file;
	file.open(filePath, std::fstream::in);
	std::string line;

	while (std::getline(file, line))
	{
		//FORMAT
		//pos index ...
		//FORMAT EXAMPLE 
		//{120,240} 1 ...
		std::string string = line;
		sf::Vector2<int> pos;
		if (string.find(",") != std::string::npos) 
		{
			pos.x = std::stoi(string.substr(1, string.find(",")));
			pos.y = std::stoi(string.substr(string.find(",") + 1, string.find("}")));
		}
		else
		{
			ERROR("loading file corrupted or just empty");
			file.close();
			return;
		}
		string.erase(0, string.find(" ") + 1);

		uint8_t type = static_cast<uint8_t>(std::stoi(string.substr(0, string.find(" "))));
		string.erase(0, string.find(" ") + 1);
		auto deserialize = deserializeFunctions[type];
		if (deserialize) {
			Entity* entity = deserialize(string);
			Tile* tile = dynamic_cast<Tile*>(entity);
			GameCharacter* gameCharacter = dynamic_cast<GameCharacter*>(entity);

			bool occupied;
			if (tile)
				occupied = isOccupied<Tile>(pos, entity->isSolid());
			else
				occupied = isOccupied<GameCharacter>(pos, entity->isSolid());

			if (!occupied) {
				if (tile) {
					nEntities++;
					tiles[type][pos] = static_cast<std::unique_ptr<Tile>>(tile);
					DEBUG("allocated tile at pos {%,%}", pos.x, pos.y);
				}
				else if (gameCharacter) {
					nEntities++;
					gameCharacters[type][pos] = static_cast<std::unique_ptr<GameCharacter>>(gameCharacter);
					DEBUG("allocated gamecharacter at pos {%,%}", pos.x, pos.y);
				}
			}
		}
		else
			DEBUG("Error trying to deserialize entity. Probably loading txt file has been corrupted.");
	}
	file.close();
}

void Map::save(const std::string& filePath) const {
	DEBUG("Saving...");

	std::fstream file;
	file.open(filePath, std::fstream::out | std::fstream::trunc); //clear the txt file
	if (!file.is_open())
		ERROR("Can't open map file");

	for (auto& tile : tiles)
		for (auto i = tile.second.begin(); i != tile.second.end(); ++i)
			file << "{" << i->first.x << "," << i->first.y << "} " << std::to_string(tile.first) << i->second->serialize() << std::endl;

	for(auto& gameCharacter: gameCharacters)
		for (auto i = gameCharacter.second.begin(); i != gameCharacter.second.end(); ++i)
			file << "{" << i->first.x << "," << i->first.y << "} " << std::to_string(gameCharacter.first) << i->second->serialize() << std::endl;

	file.close();
}

void Map::render(sf::RenderWindow& window) const {
	auto& view = window.getView();
	float top = view.getCenter().y - view.getSize().y * 0.5f - cellDim.y;
	float bottom = view.getCenter().y + view.getSize().y * 0.5 + cellDim.y;
	float left = view.getCenter().x - view.getSize().x * 0.5f - cellDim.x;
	float right = view.getCenter().x + view.getSize().x * 0.5f + cellDim.x;

	uint32_t nCells = ((bottom - top) / cellDim.y) * ((right - left) / cellDim.x);

	if (nCells < nEntities)
		for (float j = top; j < bottom; j += cellDim.y)
			for (float i = left; i < right; i += cellDim.x) {
				auto tile = get<Tile>(worldCoordToPos({ i,j }));
				auto gameCharater = get<GameCharacter>(worldCoordToPos({ i, j }));
				if (tile) tile->render(window);
				else if (gameCharater) gameCharater->render(window);
			}
	else {
		for (auto& tileType : tiles)
			for (auto& tile : tileType.second)
				tile.second->render(window);

		for (auto& gameCharacterType : gameCharacters)
			for (auto& gameCharacter : gameCharacterType.second)
				gameCharacter.second->render(window);
	}
}

template<>
void Map::remove<Tile>(const sf::Vector2<int>& pos)
{
	for (auto& tile : tiles) {
		if (tile.second.erase(pos)) {
			DEBUG("a Tile removed at pos {%,%}", pos.x, pos.y);
			return;
		}
		else
			DEBUG("no Tile at pos {%,%}", pos.x, pos.y);
	}
}

template<>
void Map::remove<GameCharacter>(const sf::Vector2<int>& pos)
{
	for (auto& gameCharacter : gameCharacters) {
		if (gameCharacter.second.erase(pos)) {
			DEBUG("a GameCharacter removed at pos {%,%}", pos.x, pos.y);
			return;
		}
		else
			DEBUG("no GameCharacter at pos {%,%}", pos.x, pos.y);
	}
}

template<>
void Map::remove<Entity>(const sf::Vector2<int>& pos) 
{
	remove<Tile>(pos);
	remove<GameCharacter>(pos);
}

template<>
Entity* Map::get<Entity>(const sf::Vector2<int>& pos) const
{
	Tile* tile = get<Tile>(pos);
	GameCharacter* gameCharacter = get<GameCharacter>(pos);

	if (tile) return tile;
	else if (gameCharacter) return gameCharacter;
	else return nullptr;
}

template<>
Tile* Map::get<Tile>(const sf::Vector2<int>& pos) const
{
	for (auto& tile : tiles)
		if (tile.second.find(pos) != tile.second.end())
			return tile.second.at(pos).get();
	return nullptr;
}

template<>
GameCharacter* Map::get<GameCharacter>(const sf::Vector2<int>& pos) const
{
	for (auto& gameCharacter : gameCharacters)
		if (gameCharacter.second.find(pos) != gameCharacter.second.end())
			return gameCharacter.second.at(pos).get();
	return nullptr;
}



template<>
bool Map::isOccupied<Tile>(const sf::Vector2<int>& pos, bool solid) const
{
	Tile* tile = get<Tile>(pos);
	GameCharacter* gameCharacter = get<GameCharacter>(pos);
	return tile || (solid && gameCharacter) || (!solid && gameCharacter && gameCharacter->isSolid());
}

template<>
bool Map::isOccupied<GameCharacter>(const sf::Vector2<int>& pos, bool solid) const
{
	Tile* tile = get<Tile>(pos);
	GameCharacter* gameCharacter = get<GameCharacter>(pos);
	return gameCharacter || (solid && tile) || (!solid && tile && tile->isSolid());
}

sf::Vector2<int> Map::worldCoordToPos(const sf::Vector2<float>& worldCoord) const 
{
	return { int(floor(worldCoord.x/ cellDim.x)),int(floor(worldCoord.y/ cellDim.y)) };
}

sf::Vector2<float> Map::posToWorldCoord(const sf::Vector2<int>& pos) const
{
	return { float(pos.x * cellDim.x),float(pos.y * cellDim.y) };
}

sf::Vector2<int> Map::getCellDim() const {
	return cellDim;
}

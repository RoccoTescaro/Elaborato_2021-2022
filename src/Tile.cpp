#include "../headers/Tile.h"

///////////////////////////WALL//////////////////////////

Wall::Wall(const sf::Vector2<float>& pos, const sf::Vector2<float>& size) : Tile(pos, size) {
	testingSprite.setFillColor({ 128, 0, 255, 128 });
}

std::string Wall::serialize() const {
	return "Wall {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "}";
}

Entity* Wall::deserialize(std::string line) {
	std::vector<std::string> parameters;
	line = line.substr(line.find("{")+1, line.size());

	size_t pos;
	while (pos = line.find(",") < line.find("}")) {
		parameters.push_back(line.substr(0, pos));
		line.erase(0, pos + 1);
	}
	
	float posX = std::stof(parameters[0]);
	float posY = std::stof(parameters[1]);
	float sizeX = std::stof(parameters[2]);
	float sizeY = std::stof(parameters[3]);
	return new Wall({ posX,posY }, { sizeX,sizeY });
}

bool Wall::isSolid() const{
	return true;
}

///////////////////////////HOLE//////////////////////////

Hole::Hole(const sf::Vector2<float>& pos, const sf::Vector2<float>& size) : Tile(pos, size) {
	testingSprite.setFillColor({ 0, 0, 0, 128 });
}

std::string Hole::serialize() const {
	return "Hole {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "}";
}

Entity* Hole::deserialize(std::string line) {
	std::vector<std::string> parameters;
	line = line.substr(line.find("{") + 1, line.size());

	size_t pos;
	while (pos = line.find(",") < line.find("}")) {
		parameters.push_back(line.substr(0, pos));
		line.erase(0, pos + 1);
	}

	float posX = std::stof(parameters[0]);
	float posY = std::stof(parameters[1]);
	float sizeX = std::stof(parameters[2]);
	float sizeY = std::stof(parameters[3]);
	return new Hole({ posX,posY }, { sizeX,sizeY });
}

bool Hole::isSolid() const {
	return true;
}

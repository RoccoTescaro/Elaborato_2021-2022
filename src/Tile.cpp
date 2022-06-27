#include "../headers/Tile.h"
#include "../headers/Log.h"

///////////////////////////WALL//////////////////////////

Wall::Wall(const sf::Vector2<int>& pos, const sf::Vector2<int>& size) : Tile(pos, size) {
	testingSprite.setFillColor({ 128, 0, 255, 64 });
}

std::string Wall::serialize() const {
	return " {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "}";
}

Entity* Wall::deserialize(std::string line) {
	std::vector<std::string> parameters;
	parseString(parameters, line);
	
	int posX = std::stoi(parameters[0]);
	int posY = std::stoi(parameters[1]);
	int sizeX = std::stoi(parameters[2]);
	int sizeY = std::stoi(parameters[3]);
	return new Wall({ posX/sizeX,posY/sizeY }, { sizeX,sizeY });
}

bool Wall::isSolid() const{
	return true;
}

///////////////////////////HOLE//////////////////////////

Hole::Hole(const sf::Vector2<int>& pos, const sf::Vector2<int>& size) : Tile(pos, size) {
	testingSprite.setFillColor({ 10, 0, 40, 64 });
}

std::string Hole::serialize() const {
	return " {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "}";
}

Entity* Hole::deserialize(std::string line) {
	std::vector<std::string> parameters;
	parseString(parameters, line);

	int posX = std::stoi(parameters[0]);
	int posY = std::stoi(parameters[1]);
	int sizeX = std::stoi(parameters[2]);
	int sizeY = std::stoi(parameters[3]);
	return new Hole({ posX/sizeX,posY/sizeY }, { sizeX,sizeY });
}

bool Hole::isSolid() const {
	return false;
}
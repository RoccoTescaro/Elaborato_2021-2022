#include "../headers/Enemy.h"

uint8_t Enemy::getInitiative() const {
	return initiative;
}

//////////////////////////MELEE//////////////////////////

Melee::Melee(const sf::Vector2<float>& pos, const sf::Vector2<float>& size) 
	: Enemy(pos, size, 100, 20, 8) 
{
	testingSprite.setFillColor({ 200, 20, 20, 128 });
}

std::string Melee::serialize() const {
	return "Melee {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "}";
}

Entity* Melee::deserialize(std::string line) {
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
	return new Melee({ posX,posY }, { sizeX,sizeY });
}

bool Melee::isSolid() const {
	return true;
}

//////////////////////////BAT///////////////////////////

Bat::Bat(const sf::Vector2<float>& pos, const sf::Vector2<float>& size) : 
	Enemy(pos, size, 100, 20, 5) 
{
	testingSprite.setFillColor({ 220, 20, 20, 128 });
}

std::string Bat::serialize() const {
	return "Bat {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "}";
}

Entity* Bat::deserialize(std::string line) {
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
	return new Bat({ posX,posY }, { sizeX,sizeY });
}

bool Bat::isSolid() const {
	return false;
}

////////////////////////RANGED///////////////////////////

Ranged::Ranged(const sf::Vector2<float>& pos, const sf::Vector2<float>& size) :
	Enemy(pos, size, 100, 20, 3)
{
	testingSprite.setFillColor({ 240, 20, 20, 128 });
}

std::string Ranged::serialize() const {
	return "Ranged {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "}";
}

Entity* Ranged::deserialize(std::string line) {
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
	return new Bat({ posX,posY }, { sizeX,sizeY });
}

bool Ranged::isSolid() const {
	return true;
}


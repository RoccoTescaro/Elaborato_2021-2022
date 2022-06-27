#include "../headers/GameCharacter.h"
#include <iostream>

uint8_t GameCharacter::getInitiative() const {
	return initiative;
}

//////////////////////////MELEE//////////////////////////

Melee::Melee(const sf::Vector2<int>& pos, const sf::Vector2<int>& size, uint8_t hp, uint8_t ap)
	: GameCharacter(pos, size, 100, hp, 20, ap, 8)
{
	testingSprite.setFillColor({ 200, 20, 20, 64 });
}

std::string Melee::serialize() const {
	return " {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "," +
		std::to_string(hp) + "," +
		std::to_string(ap) + "}";
}

Entity* Melee::deserialize(std::string line) {
	std::vector<std::string> parameters;
	parseString(parameters, line);

	int posX = std::stoi(parameters[0]);
	int posY = std::stoi(parameters[1]);
	int sizeX = std::stoi(parameters[2]);
	int sizeY = std::stoi(parameters[3]);
	uint8_t hp = std::stoi(parameters[4]);
	uint8_t ap = std::stoi(parameters[5]);
	return new Melee({ posX/sizeX,posY/sizeY }, { sizeX,sizeY }, hp, ap);
}

bool Melee::isSolid() const {
	return true;
}

//////////////////////////BAT///////////////////////////

Bat::Bat(const sf::Vector2<int>& pos, const sf::Vector2<int>& size, uint8_t hp, uint8_t ap) :
	GameCharacter(pos, size, 100, hp, 20, ap, 5)
{
	testingSprite.setFillColor({ 220, 20, 20, 64 });
}

std::string Bat::serialize() const {
	return " {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "," +
		std::to_string(hp) + "," +
		std::to_string(ap) + "}";
}

Entity* Bat::deserialize(std::string line) {
	std::vector<std::string> parameters;
	parseString(parameters, line);

	int posX = std::stoi(parameters[0]);
	int posY = std::stoi(parameters[1]);
	int sizeX = std::stoi(parameters[2]);
	int sizeY = std::stoi(parameters[3]);
	uint8_t hp = std::stoi(parameters[4]);
	uint8_t ap = std::stoi(parameters[5]);
	return new Bat({ posX/sizeX,posY/sizeY }, { sizeX,sizeY }, hp, ap);
}

bool Bat::isSolid() const {
	return false;
}

////////////////////////RANGED///////////////////////////

Ranged::Ranged(const sf::Vector2<int>& pos, const sf::Vector2<int>& size, uint8_t hp, uint8_t ap) :
	GameCharacter(pos, size, 100, hp, 20, ap, 3)
{
	testingSprite.setFillColor({ 240, 20, 20, 64 });
}

std::string Ranged::serialize() const {
	return " {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "," +
		std::to_string(hp) + "," +
		std::to_string(ap) + "}";
}

Entity* Ranged::deserialize(std::string line) {
	std::vector<std::string> parameters;
	parseString(parameters, line);

	int posX = std::stoi(parameters[0]);
	int posY = std::stoi(parameters[1]);
	int sizeX = std::stoi(parameters[2]);
	int sizeY = std::stoi(parameters[3]);
	uint8_t hp = std::stoi(parameters[4]);
	uint8_t ap = std::stoi(parameters[5]);
	return new Ranged({ posX/sizeX,posY/sizeY }, { sizeX,sizeY }, hp, ap);
}

bool Ranged::isSolid() const {
	return true;
}

////////////////////////RANGED///////////////////////////

Player::Player(const sf::Vector2<int>& pos, const sf::Vector2<int>& size, uint8_t hp, uint8_t ap)
	: GameCharacter(pos, size, 100, hp, 20, ap, 0)
{
	testingSprite.setFillColor({ 20, 200, 20, 64 });
}

std::string Player::serialize() const {
	return " {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "," +
		std::to_string(hp) + "," +
		std::to_string(ap) + "}";
}

Entity* Player::deserialize(std::string line) {
	std::vector<std::string> parameters;
	parseString(parameters, line);

	int posX = std::stoi(parameters[0]);
	int posY = std::stoi(parameters[1]);
	int sizeX = std::stoi(parameters[2]);
	int sizeY = std::stoi(parameters[3]);
	uint8_t hp = std::stoi(parameters[4]);
	uint8_t ap = std::stoi(parameters[5]);
	return new Player({ posX/sizeX,posY/sizeY }, { sizeX,sizeY }, hp, ap);
}

bool Player::isSolid() const {
	return true;
}
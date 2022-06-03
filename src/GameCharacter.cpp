#include "../headers/GameCharacter.h"
#include "../headers/Map.h"
#include "../headers/Pathfinding.h"
#include <iostream>


uint8_t GameCharacter::getInitiative() const {
	return initiative;
}

//////////////////////////MELEE//////////////////////////
PathAlgorithm* Melee::movementStrategy=nullptr;

Melee::Melee(const sf::Vector2<float>& pos, const sf::Vector2<float>& size, uint8_t hp, uint8_t ap)
	: GameCharacter(pos, size, 100, hp, 20, ap, 8)
{	
	testingSprite.setFillColor({ 200, 20, 20, 64 });
}
void Melee::setMovement(Map &map){

	if(!Melee::movementStrategy)
		Melee::movementStrategy=new A_Star(map);

}


PathAlgorithm*  Melee::getMovement() {

	return Melee::movementStrategy;

}

std::string Melee::serialize() const {
	return "Melee {" +
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

	float posX = std::stof(parameters[0]);
	float posY = std::stof(parameters[1]);
	float sizeX = std::stof(parameters[2]);
	float sizeY = std::stof(parameters[3]);
	uint8_t hp = std::stoi(parameters[4]);
	uint8_t ap = std::stoi(parameters[5]);
	return new Melee({ posX,posY }, { sizeX,sizeY }, hp, ap);
}

bool Melee::isSolid() const {
	return true;
}

//////////////////////////BAT///////////////////////////
PathAlgorithm* Bat::movementStrategy=nullptr;

Bat::Bat(const sf::Vector2<float>& pos, const sf::Vector2<float>& size, uint8_t hp, uint8_t ap) :
	GameCharacter(pos, size, 100, hp, 20, ap, 5)
{
	testingSprite.setFillColor({ 220, 20, 20, 64 });
}

void Bat::setMovement(Map &map){

	if(!Bat::movementStrategy)
		Bat::movementStrategy=new A_Star(map);

}


PathAlgorithm*  Bat::getMovement() {

	return Bat::movementStrategy;

}
std::string Bat::serialize() const {
	return "Bat {" +
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

	float posX = std::stof(parameters[0]);
	float posY = std::stof(parameters[1]);
	float sizeX = std::stof(parameters[2]);
	float sizeY = std::stof(parameters[3]);
	uint8_t hp = std::stoi(parameters[4]);
	uint8_t ap = std::stoi(parameters[5]);
	return new Bat({ posX,posY }, { sizeX,sizeY }, hp, ap);
}

bool Bat::isSolid() const {
	return false;
}

////////////////////////RANGED///////////////////////////
PathAlgorithm* Ranged::movementStrategy=nullptr;

Ranged::Ranged(const sf::Vector2<float>& pos, const sf::Vector2<float>& size, uint8_t hp, uint8_t ap) :
	GameCharacter(pos, size, 100, hp, 20, ap, 3)
{
	testingSprite.setFillColor({ 240, 20, 20, 64 });
}
void Ranged::setMovement(Map &map){

	if(!Ranged::movementStrategy)
		Ranged::movementStrategy=new A_Star(map);

}


PathAlgorithm*  Ranged::getMovement() {

	return Ranged::movementStrategy;

}


std::string Ranged::serialize() const {
	return "Ranged {" +
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

	float posX = std::stof(parameters[0]);
	float posY = std::stof(parameters[1]);
	float sizeX = std::stof(parameters[2]);
	float sizeY = std::stof(parameters[3]);
	uint8_t hp = std::stoi(parameters[4]);
	uint8_t ap = std::stoi(parameters[5]);
	return new Bat({ posX,posY }, { sizeX,sizeY }, hp, ap);
}

bool Ranged::isSolid() const {
	return true;
}

////////////////////////Player///////////////////////////

PathAlgorithm* Player::movementStrategy=nullptr;

Player::Player(const sf::Vector2<float>& pos, const sf::Vector2<float>& size, uint8_t hp, uint8_t ap)
	: GameCharacter(pos, size, 100, hp, 20, ap, 0)
{
	testingSprite.setFillColor({ 20, 200, 20, 64 });
}
void Player::setMovement(Map &map){

	if(!Player::movementStrategy)
		Player::movementStrategy=new A_Star(map);

}


PathAlgorithm*  Player::getMovement() {

	return Player::movementStrategy;

}


std::string Player::serialize() const {
	return "Player {" +
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

	float posX = std::stof(parameters[0]);
	float posY = std::stof(parameters[1]);
	float sizeX = std::stof(parameters[2]);
	float sizeY = std::stof(parameters[3]);
	uint8_t hp = std::stoi(parameters[4]);
	uint8_t ap = std::stoi(parameters[5]);
	return new Player({ posX,posY }, { sizeX,sizeY }, hp, ap);
}

bool Player::isSolid() const {
	return true;
}

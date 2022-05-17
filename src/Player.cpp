#include "../headers/Player.h"

Player::Player(const sf::Vector2<float>& pos, const sf::Vector2<float>& size)
	: GameCharacter(pos, size, 100, 20)
{
	testingSprite.setFillColor({ 20, 200, 20, 128 });
}

std::string Player::serialize() const {
	return "Player {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "}";
}

Entity* Player::deserialize(std::string line) {
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
	return new Player({ posX,posY }, { sizeX,sizeY });
}

bool Player::isSolid() const {
	return true;
}
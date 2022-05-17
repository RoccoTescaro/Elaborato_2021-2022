#include "../headers/Entity.h"

Entity::Entity(const sf::Vector2<float>& pos, const sf::Vector2<float>& size) {
	testingSprite.setPosition(pos);
	testingSprite.setSize(size);
}

void Entity::render(sf::RenderWindow& window) {
	window.draw(testingSprite);
}

void Entity::move(const sf::Vector2<float>& pos) {
	testingSprite.setPosition(pos);
}

void Entity::parseString(std::vector<std::string>& parameters, std::string& line) {
	line = line.substr(line.find("{") + 1, line.size());

	size_t pos = line.find(",");
	while (pos < line.find("}")) {
		parameters.push_back(line.substr(0, pos));
		line.erase(0, pos + 1);
		pos = line.find(",");
	}
	parameters.push_back(line.substr(0, line.find("}")));
}
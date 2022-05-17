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
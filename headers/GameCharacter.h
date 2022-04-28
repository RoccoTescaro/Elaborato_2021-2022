#include "Entity.h"

class GameCharacter : public Entity {
public:
	GameCharacter(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim) : Entity(cellDim) {
		sprite.setPosition(pos.x * cellDim.x, pos.y * cellDim.y);
		sprite.setSize(cellDim);
		sprite.setFillColor(sf::Color(0, 0, 255, 255));
	}
};

#include <SFML/Graphics.hpp>
class Entity {
public:
	Entity(const sf::Vector2<float>& cellDim_) : cellDim(cellDim_) {}
	virtual ~Entity() {}
	void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}

	void move(const sf::Vector2<int>& pos) {
		sprite.setPosition(pos.x*cellDim.x,pos.y*cellDim.y);
	}
protected:
	const sf::Vector2<float>& cellDim; 
	sf::RectangleShape sprite;
};
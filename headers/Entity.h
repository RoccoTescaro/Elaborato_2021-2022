
#include <SFML/Graphics.hpp>
class Entity {
public:
	Entity() {}
	virtual ~Entity() {}
	void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}
protected:
sf::Sprite sprite;
};
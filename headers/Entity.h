
#include <SFML/Graphics.hpp>
class Entity {
public:
	Entity() {}
	virtual ~Entity() {}
	void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	void update();
	virtual void execute(Entity& e); 
private:
sf::Sprite sprite;
};
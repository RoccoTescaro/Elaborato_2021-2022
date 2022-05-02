


#ifndef UNTITLED_ENTITY_H
#define UNTITLED_ENTITY_H



#include <SFML/Graphics.hpp>
class Entity {
public:
	Entity(sf::Sprite& sprite) {}
	virtual ~Entity() {}
	void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	void update();
	virtual void execute(Entity& e); 
private:
sf::Sprite sprite;
};


#endif //UNTITLED_ENTITY_H

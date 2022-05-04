
//todo untitled

#ifndef ENTITY_H
#define ENTITY_H



#include <SFML/Graphics.hpp>
class Entity {
public:
	Entity(sf::Texture& texture):sprite(texture) {}
	virtual ~Entity()=0;
	virtual void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	virtual void update(const float &deltaTime);
	virtual void execute(Entity& e); 
private:
sf::Sprite sprite;
};


#endif //UNTITLED_ENTITY_H

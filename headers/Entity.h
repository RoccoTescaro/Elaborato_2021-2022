
//todo untitled

#ifndef ENTITY_H
#define ENTITY_H



#include <SFML/Graphics.hpp>
class Entity {
public:
	Entity(sf::Texture& texture):sprite(texture) {}
	virtual ~Entity(){};
	virtual void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	virtual void update(const float &deltaTime)=0;
	virtual void execute(Entity& e)=0; 
private:
sf::Sprite sprite;
};


#endif //ENTITY_H

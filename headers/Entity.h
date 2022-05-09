
//todo untitled

#ifndef ENTITY_H
#define ENTITY_H



#include <SFML/Graphics.hpp>
class Entity {
public:
	Entity(sf::Texture& texture,const sf::Vector2<float>& cellDim_):Rsprite(texture),cellDim(cellDim_) {}
	virtual ~Entity(){};
	virtual void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	virtual void update(const float &deltaTime)=0;
	virtual void execute(Entity& e)=0; 
	void move(const sf::Vector2<int>& pos) {
		sprite.setPosition(pos.x*cellDim.x,pos.y*cellDim.y);
	}
protected:
	sf::Sprite Rsprite;
	const sf::Vector2<float>& cellDim; 
	sf::RectangleShape sprite;
};


#endif //ENTITY_H

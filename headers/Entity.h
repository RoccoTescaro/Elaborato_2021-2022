
//todo untitled

#ifndef ENTITY_H
#define ENTITY_H



#include <SFML/Graphics.hpp>
#include <iostream>
class Entity {
public:
	Entity(const sf::Color color, const sf::Vector2<float>& cellDim_) : cellDim(cellDim_) { sprite.setFillColor(color); }
	virtual ~Entity(){};
	virtual void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	virtual void update(const float &deltaTime)=0;
	virtual void execute(Entity& e)=0; 
	void move(const sf::Vector2<int>& pos) {
		sprite.setPosition(pos.x*cellDim.x,pos.y*cellDim.y);
	}

	virtual std::string serialize() { 
		std::cout << typeid(*this).name() << std::endl;
		return ""; };
protected:
	sf::Sprite Rsprite;
	const sf::Vector2<float>& cellDim; 
	sf::RectangleShape sprite;
};


#endif //ENTITY_H


//todo untitled

#ifndef ENTITY_H
#define ENTITY_H



#include <SFML/Graphics.hpp>
class Entity {
public:
	Entity(sf::Vector2<int> pos,sf::Texture& texture,const sf::Vector2<float>& cellDim_, bool solid):Rsprite(texture),cellDim(cellDim_), solid(solid) {}
	virtual ~Entity(){};
	virtual void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	virtual void update(const float &deltaTime)=0;
	virtual void execute(Entity& e)=0; 
	void move(const sf::Vector2<int>& pos) {
		sprite.setPosition(pos.x*cellDim.x,pos.y*cellDim.y);
	}
	virtual bool isSolid(bool flying=false);
protected:
	bool solid;
	sf::Vector2<int> pos;
	sf::Sprite Rsprite;
	const sf::Vector2<float>& cellDim; 
	sf::RectangleShape sprite;
};


#endif //ENTITY_H

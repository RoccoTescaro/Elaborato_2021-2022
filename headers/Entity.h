#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
<<<<<<< HEAD
	Entity(const sf::Color color,sf::Vector2<int> pos,const sf::Vector2<float>& cellDim_, bool solid):cellDim(cellDim_), solid(solid) {sprite.setFillColor(color);}
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
=======
	Entity(const sf::Vector2<float>& pos, const sf::Vector2<float>& size);
	virtual ~Entity() = default;
>>>>>>> Map

	virtual void render(sf::RenderWindow& window);
	virtual void update(const float& dt) = 0;
	virtual void execute(Entity* entity) = 0;

	void move(const sf::Vector2<float>& pos); //#TODO implements animations
	
	virtual std::string serialize() const = 0;
	//can't be virtual (couse must be static), but each leaf must implement it
	//static Entity* deserialize(std::string line); 

	virtual bool isSolid() const = 0;
protected:
<<<<<<< HEAD
	bool solid;
	sf::Vector2<int> pos;
	const sf::Vector2<float>& cellDim; 
	sf::RectangleShape sprite;
=======
	static void parseString(std::vector<std::string>& parameters, std::string& line);

	sf::RectangleShape testingSprite;
>>>>>>> Map
};


#endif //ENTITY_H

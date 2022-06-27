#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
	Entity(const sf::Vector2<int>& pos, const sf::Vector2<int>& size);
	virtual ~Entity() = default;

	virtual void render(sf::RenderWindow& window);
	virtual void update(const float& dt) = 0;
	virtual void execute(Entity* entity) = 0;

	void move(const sf::Vector2<float>& pos); //#TODO implements animations
	
	virtual std::string serialize() const = 0;
	//can't be virtual (couse must be static), but each leaf must implement it
	//static Entity* deserialize(std::string line); 

	virtual bool isSolid() const = 0;
protected:
	static void parseString(std::vector<std::string>& parameters, std::string& line);

	sf::RectangleShape testingSprite;
};


#endif //ENTITY_H

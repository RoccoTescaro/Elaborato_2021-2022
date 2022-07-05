#ifndef LIGHTINGSYSTEM_H
#define LIGHTINGSYSTEM_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map;

class LightingSystem 
{
public:
	void addLight(const sf::Vector2<int>& lightPos, int radius, Map& map);
	void render(sf::RenderWindow& window, Map& map);
private:
	std::vector<sf::Vector2<int>> border;
};

#endif //LIGHTINGSYSTEM_H


#ifndef LIGHTINGSYSTEM_H
#define LIGHTINGSYSTEM_H

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <unordered_map>
#include <queue>

class Map;

class LightingSystem //TODO FIX BORDER BUG
{
public:
	void updateCell(const sf::Vector2<int>& pos, const Map& map);

	void updateVision(const sf::Vector2<float>& light, float radius, const sf::View& view);

	void render(sf::RenderWindow& window);  
private:
	sf::Vector2<float> findRelativePoint(const sf::Vector2<float>& start, const sf::Vector2<int>& dir, const Map& map);

	uint32_t addEdge(sf::Vector2<float> start, sf::Vector2<float> end);

	struct hash {
		std::size_t operator () (const sf::Vector2<float>& point) const {
			std::size_t h1 = std::hash<float>()(point.x);
			std::size_t h2 = std::hash<float>()(point.y);
			return h1 ^ h2;
		}
	};
	
	struct Edge {
		sf::Vector2<float> start;
		sf::Vector2<float> end;

		const Edge& operator = (const Edge & edge){
			start = edge.start;
			end = edge.end;
			return *this;
		}
	};

	std::unordered_set<sf::Vector2<float>, hash> points;
	std::vector<std::tuple<float, float, float>> visionPoints;

	std::unordered_map<uint32_t, Edge> edges{};
	std::queue<uint32_t> freeIndexs{};

	std::unordered_map<sf::Vector2<float>, uint32_t, hash> vEdges; //vertical
	std::unordered_map<sf::Vector2<float>, uint32_t, hash> hEdges; //horizontal 
};

#endif //LIGHTINGSYSTEM_H


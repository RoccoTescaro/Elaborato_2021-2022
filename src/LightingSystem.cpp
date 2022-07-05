#include "../headers/LightingSystem.h"
#include "../headers/Map.h"
#define PI 3.14159265358979323846



void LightingSystem::addLight(const sf::Vector2<int>& lightPos, int radius, Map& map)
{
	border.clear();

	int nRays = radius * 8; 
	float dAlpha = PI * 2 / nRays;

	for (int i = 0; i < nRays; i++)
	{
		//DDA Algorithm
		//(Bresenham’s Line Drawing Algorithm is faster but would need some changes to work with negatives values)

		int dx = std::round(radius * std::cosf(dAlpha * i));
		int dy = std::round(radius * std::sinf(dAlpha * i));

		int step = std::max<int>(std::abs(dx), std::abs(dy));

		float xIncrement = dx / (float)step;
		float yIncrement = dy / (float)step;

		float x = lightPos.x + xIncrement;
		float y = lightPos.y + yIncrement;

		sf::Vector2<int> pos = { (int)std::round(x),(int)std::round(y) };

		for (int i = 1; i < step && !map.isOccupied<Tile>(pos) ; ++i)
		{
			//border.insert(pos);
			x += xIncrement;
			y += yIncrement;
			pos = { (int)std::round(x),(int)std::round(y) };
		}

		border.push_back(pos);
	}
}

void LightingSystem::render(sf::RenderWindow& window, Map& map)
{
	sf::ConvexShape shape;
	sf::RenderStates state;
	state.blendMode = sf::BlendAdd;
	shape.setPointCount(border.size());
	int i = 0;
	for (auto& v : border) {
		shape.setPoint(i++, sf::Vector2<float>{(v.x + 0.5f) * map.getCellDim().x, (v.y + 0.5f) * map.getCellDim().y});
		sf::CircleShape point(12);
		point.setOrigin(12,12);
		point.setFillColor(sf::Color(255, 0, 0));
		point.setPosition((v.x+0.5)*map.getCellDim().x, (v.y+0.5)*map.getCellDim().y);
		window.draw(point);
	}
	shape.setFillColor(sf::Color(0, 255, 0));
	window.draw(shape,state);
}

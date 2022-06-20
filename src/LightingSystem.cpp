#include "../headers/LightingSystem.h"
#include "../headers/Map.h"
#include <iostream>
#include "../headers/Log.h"

#define INVALID_POINT sf::Vector2<float>{-1,-1}
#define EPSILON 0.00001

void LightingSystem::updateCell(const sf::Vector2<int>& pos, const Map& map)
{
	//if (!map(pos, Map::entityLayer::tileLayer) || !map.isOccupied(pos, Map::entityLayer::tileLayer))
		//return;
	
	sf::Vector2<int> relativePos[4] =
	{
		{ 0, 0}, //TOP LEFT
		{ 1, 0}, //TOP RIGHT
		{ 0, 1}, //BOTTOM LEFT
		{ 1, 1}, //BOTTOM RIGHT
	};


	//update points
	for (int i = 0; i < 4; i++) 
	{
		int nNeighbours = 0;
		for(int j = 0; j < 4; j++)
			if (map(pos.x - 1 + relativePos[j].x + relativePos[i].x, pos.y - 1 + relativePos[j].y + relativePos[i].y, Map::entityLayer::tileLayer) &&
				map(pos.x - 1 + relativePos[j].x + relativePos[i].x, pos.y - 1 + relativePos[j].y + relativePos[i].y, Map::entityLayer::tileLayer)->isSolid())
				nNeighbours++;
		
		sf::Vector2<float> point = { (pos.x + relativePos[i].x) * map.getCellDim().x, (pos.y + relativePos[i].y) * map.getCellDim().y };

		if (nNeighbours % 2) 
			points.insert(point);
		else 
			points.erase(point);
	}

	//update edges
	for (int i = 0; i < 4; i++)
	{
		sf::Vector2<float> point = { (pos.x + relativePos[i].x) * map.getCellDim().x, (pos.y + relativePos[i].y) * map.getCellDim().y };

		sf::Vector2<float> hBefore = findRelativePoint(point, { -1,0 }, map);
		sf::Vector2<float> vBefore = findRelativePoint(point, { 0,-1 }, map);
		sf::Vector2<float> hAfter = findRelativePoint(point, { 1,0 }, map);
		sf::Vector2<float> vAfter = findRelativePoint(point, { 0,1 }, map);

		uint32_t edgeIndex = 0;

		if (points.contains(point)) { //added
			//find out if point is a starting point or an ending one
			if (hBefore == INVALID_POINT || (hBefore != INVALID_POINT && edges.find(hEdges[hBefore]) != edges.end() && edges[hEdges[hBefore]].end == hBefore) ) { //point is a "starting point"
				edgeIndex = addEdge(point, hAfter);
				hEdges[point] = edgeIndex;
				hEdges[hAfter] = edgeIndex;
			}
			else { // point is an "ending point"
				edgeIndex = addEdge(hBefore, point);
				hEdges[hBefore] = edgeIndex;
				hEdges[point] = edgeIndex;
			}

			//find out if point is a starting point or an ending one
			if (vBefore == INVALID_POINT || (vBefore != INVALID_POINT && edges.find(vEdges[vBefore]) != edges.end() && edges[vEdges[vBefore]].end == vBefore)) { //point is a "starting point"
				edgeIndex = addEdge(point, vAfter);
				vEdges[point] = edgeIndex;
				vEdges[vAfter] = edgeIndex;
			}
			else { // point is an "ending point"
				edgeIndex = addEdge(vBefore, point);
				vEdges[vBefore] = edgeIndex;
				vEdges[point] = edgeIndex;
			}
		}
		else { //removed

			sf::Vector2<float> hStart = edges[hEdges[hBefore]].start;
			sf::Vector2<float> vStart = edges[vEdges[vBefore]].start;

			freeIndexs.push(hEdges[point]);
			edges.erase(hEdges[point]);
			hEdges.erase(point);

			if (hBefore != INVALID_POINT && hStart == hBefore) {
				uint32_t index = addEdge(hBefore, hAfter);
				hEdges[hBefore] = index;
				hEdges[hAfter] = index;
			}

			freeIndexs.push(vEdges[point]);
			edges.erase(vEdges[point]);
			vEdges.erase(point);

			if (vBefore != INVALID_POINT && vStart == vBefore) {
				uint32_t index = addEdge(vBefore, vAfter);
				vEdges[vBefore] = index;
				vEdges[vAfter] = index;
			}

			
		}

	}

	DEBUG("edges size = %", edges.size());
	for (auto& edge : edges)
		DEBUG("edge index = %, edge value = {{%,%},{%,%}}", edge.first, edge.second.start.x, edge.second.start.y, edge.second.end.x, edge.second.end.y);

}

void LightingSystem::updateVision(const sf::Vector2<float>& light, float radius, const sf::View& view)
{
	visionPoints.clear();
	
	for (auto& point : points) {

		float baseAngle = std::atanf(point.y/point.x);
		sf::Vector2<float> target;

		for (int i = -1; i <= 1; i++)
		{
			float angle = baseAngle + i * EPSILON;
			target = { radius * std::cosf(angle),radius * std::sinf(angle) };

			float minT1 = INFINITY;
			std::tuple<float,float,float> minPoint;

			for (auto& edge : edges) {

				sf::Vector2<float> segment = edge.second.end - edge.second.start;

				if (std::abs(segment.x - target.x) > 0 && std::abs(segment.y - target.y) > 0)
				{
					float t1 = (target.x * (edge.second.start.y - light.y) + target.y * (light.x - edge.second.start.x)) / (segment.x * target.y - segment.y * target.x);
					float t2 = (edge.second.start.x + segment.x * t1 - light.x) / target.x;

					if (t1 > 0 && t2 >= 0 && t2 <= 1 && t1 < minT1) 
					{
						minT1 = t1;
						float minX = light.x + target.x * t1;
						float minY = light.y + target.y * t1;
						float minAngle = std::atanf((minY-light.y)/(minX-light.x));
						minPoint = {minX,minY,minAngle};
					}
				}

			}

			visionPoints.push_back(minPoint);
			
		}

	}

	sort(visionPoints.begin(), visionPoints.end(),
		[&](const std::tuple<float, float, float>& t1, const std::tuple<float, float, float>& t2)
		{
			return get<2>(t1) < get<2>(t2);
		});

}

void LightingSystem::render(sf::RenderWindow& window)
{
	for (auto& edge : edges) {
		sf::Vertex line[2];
		line[0] = edge.second.start;
		line[1] = edge.second.end;
		window.draw(line, 2, sf::Lines);
	}

	for (auto& point : points) {
		sf::CircleShape circle(4);
		circle.setOrigin(4,4);
		circle.setPosition(point);
		circle.setFillColor(sf::Color(255, 0, 0, 255));
		window.draw(circle);
	}
}

sf::Vector2<float> LightingSystem::findRelativePoint(const sf::Vector2<float>& start, const sf::Vector2<int>& dir, const Map& map)
{
	sf::Vector2<float> point = start;

	while (point.x > 0 && point.x < map.getDim().x * map.getCellDim().x &&
		point.y > 0 && point.y < map.getDim().y * map.getCellDim().y)
	{
		point += {dir.x* map.getCellDim().x, dir.y* map.getCellDim().y};
		if (points.contains(point)) return point;
	}

	return INVALID_POINT;
}

uint32_t LightingSystem::addEdge(sf::Vector2<float> start, sf::Vector2<float> end)
{

	for (auto& edge : edges)
		if (edge.second.start == start && edge.second.end == end)
			return edge.first;


	uint32_t index;
	if (freeIndexs.size() != 0) {
		index = freeIndexs.front();
		freeIndexs.pop();
	}
	else
		index = edges.size();

	edges[index] = {start,end};
	DEBUG("add edge: {%,{{%,%},{%,%}}}", index, start.x, start.y, end.x, end.y);
	
	return edges.size();

}



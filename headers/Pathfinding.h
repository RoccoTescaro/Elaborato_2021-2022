

#ifndef PATHFINDING_H
#define PATHFINDING_H
#include <SFML/Graphics.hpp>
#include <list>
#include <bits/stdc++.h>

using namespace sf;


class Map;
typedef std::pair<int,Vector2i>Pair;
struct Compare
{
    bool operator ()( const Pair &p1, 
                      const Pair &p2 ) const
    {
        return ( p1.first  <  p2.first );
    }
};


class PathAlgorithm{
    public:
        struct node{

            sf::Vector2i parentPos;
            int g;
            int h;
            int f;

        };
        int calculateHValue(Vector2i pos, Vector2i target);
        bool isDestination(Vector2i pos,Vector2i target);
        bool isValid(Vector2i pos, bool flying);
        PathAlgorithm(Map &map): map(map){}
        virtual std::list<Vector2i> findPath(Vector2i start, Vector2i end, bool flying,sf::RenderWindow &window)=0;
    protected:
        Map &map;
};

class A_Star:public PathAlgorithm{
    public:
        A_Star(Map &map): PathAlgorithm(map){}
        std::list<Vector2i> tracePath(std::vector<std::vector<node>> nodeInfo,Vector2i target);
        std::list<Vector2i> findPath(Vector2i start, Vector2i end, bool flying,sf::RenderWindow &window) override;
};

class DiglettMovement:public PathAlgorithm{
    public:
        DiglettMovement(Map &map): PathAlgorithm(map){}
        std::list<Vector2i> findPath(Vector2i start, Vector2i playerPos, bool flying,sf::RenderWindow &window
    ) override;
};




#endif //PATHFINDING_H

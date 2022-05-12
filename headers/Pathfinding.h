

#ifndef PATHFINDING_H
#define PATHFINDING_H
#include <SFML/Graphics.hpp>
#include <list>
#include "Map.h"
#include <bits/stdc++.h>

using namespace sf;

typedef std::pair<int,Vector2i>Pair;



class PathAlgorithm{
    public:
        struct node{

            sf::Vector2i parentPos;
            int g;
            int h;
            int f;

        };
        bool isValid(Vector2i pos, bool flying);
        PathAlgorithm(Map &map): map(map){}
        virtual std::list<Vector2i> findPath(Vector2i start, Vector2i end, bool flying)=0;
    protected:
        Map &map;
};

class A_Star:public PathAlgorithm{
    public:
        A_Star(Map &map): PathAlgorithm(map){}
        std::list<Vector2i> findPath(Vector2i start, Vector2i end, bool flying) override;
};

class DiglettMovement:public PathAlgorithm{
    public:
        DiglettMovement(Map &map): PathAlgorithm(map){}
        std::list<Vector2i> findPath(Vector2i start, Vector2i playerPos, bool flying) override;
};




#endif //PATHFINDING_H

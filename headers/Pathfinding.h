

#ifndef PATHFINDING_H
#define PATHFINDING_H

class Map{};

class PathAlgorithm{};

class  Pathfinding{
    public:
        Pathfinding(Map &map):map(map), aStar(PathAlgorithm()){
        }
    private:
        Map &map;
        PathAlgorithm aStar; 


};



#endif //PATHFINDING_H

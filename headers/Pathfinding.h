

#ifndef PATHFINDING_H
#define PATHFINDING_H
#include <SFML/Graphics.hpp>
#include <list>
#include "Player.h"

using namespace sf;

class Map{};

class PathAlgorithm{
    public:
        PathAlgorithm(Map &map): map(map){}
        virtual std::list<Vector2i> findPath(Vector2i start, Vector2i end, bool flying)=0;
    private:
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

class  Pathfinding{
    public:
        Pathfinding(Map &map,Player &Player):aStar(A_Star(map)),  map(map),dMovement(DiglettMovement(map)){}
        std::list<Vector2i> findPath(Vector2i subject, Vector2i target); 
                                /*  if PLAYER
                                        aStar:
                                        target = click position;
                                        flying = false;


                                    if ENEMY

                                        if DIGLETT                      i diglet non usano il target come  
                                            dMovement                   casella di destinazione macome riferimento                    
                                            target = playerpos          per il calcolo della cella bersaglio
                                            flying = false
                                        else
                                            aStar
                                            target = playerpos
                                            flying = false
                                */

    private:
        A_Star aStar;
        DiglettMovement dMovement;
        Map &map;



};



#endif //PATHFINDING_H

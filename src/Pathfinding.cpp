#include "../headers/Pathfinding.h"


std::list<Vector2i> Pathfinding::findPath(Vector2i subject, Vector2i target){
    
    return aStar.findPath(subject,target,map[subject].canFly());

    
}
#include "../headers/Tile.h"

bool Hole::isSolid(bool flying){
    if(flying){
        return false;
    }else{
        return solid;
    }

}
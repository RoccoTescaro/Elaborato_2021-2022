

#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

#include "GameCharacter.h"

class Player:public GameCharacter{
    public:
        Player(sf::Texture &texture, int maxActionPoints, int maxHP,int init,bool flying):AP(0),GameCharacter(texture, maxActionPoints, maxHP){}
    private:
        int AP;
};


#endif //UNTITLED_PLAYER_H

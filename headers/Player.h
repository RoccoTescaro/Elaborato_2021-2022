

#ifndef PLAYER_H
#define PLAYER_H

#include "GameCharacter.h"

class Player:public GameCharacter{
    public:
        Player(sf::Texture &texture, int maxAP, int maxHP):AP(0),GameCharacter(texture, maxAP, maxHP,GameCharacter::GCType::Player){}
    private:
        int AP;
};


#endif //PLAYER_H

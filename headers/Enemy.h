
#ifndef UNTITLED_ENEMY_H
#define UNTITLED_ENEMY_H

#include "GameCharacter.h"

class Enemy:public GameCharacter{
    public:
        Enemy(sf::Texture &texture,int maxAP,int maxHP,int init,bool flying,GCType gcType , sf::Vector2f skinPos):init(init), flying(flying), skinPos(skinPos),GameCharacter(texture, maxAP, maxHP,gcType){}
    private:
        int init;
        bool flying;
        sf::Vector2f skinPos;
        
};


class Melee:public Enemy{
    public:
        Melee(sf::Texture &texture,int maxAP,int maxHP,int init,bool flying):Enemy(texture, maxAP, 10/*HP*/,0/*init*/,false,GameCharacter::GCType::Melee ,{1,1}){}//INSERIRE SKINPOS
    };


class Bat:public Enemy{
    public:
        Bat(sf::Texture &texture,int maxAP,int maxHP,int init,bool flying):Enemy(texture, maxAP, 8/*HP*/,5/*init*/,true,GameCharacter::GCType::Ranged ,{1,1}){}//INSERIRE SKINPOS
    };


class Ranged:public Enemy{
    public:
        Ranged(sf::Texture &texture,int maxAP,int maxHP,int init,bool flying):Enemy(texture, maxAP, 5/*HP*/,3/*init*/ ,false,GameCharacter::GCType::Diglett,{1,1}){}//INSERIRE SKINPOS
    };



#endif //UNTITLED_ENEMY_H

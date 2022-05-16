
#ifndef ENEMY_H
#define ENEMY_H

#include "GameCharacter.h"

class Enemy:public GameCharacter{
    public:
        bool canFly() override;
        Enemy(const sf::Color& color,int maxAP,int maxHP,int init,bool flying,GCType gcType , sf::Vector2f skinPos, sf::Vector2<int> spawnPos):init(init), flying(flying), skinPos(skinPos),GameCharacter(color, maxAP, maxHP,gcType,spawnPos){}
    private:
        int init;
        bool flying;
        sf::Vector2f skinPos;
        
};
//
//
//class Melee:public Enemy{
//    public:
//
//	void update(const float &deltaTime) override{};
//	void execute(Entity& e) override {}; 
//
//        Melee(sf::Texture &texture,int maxAP,int maxHP,int init,bool flying, sf::Vector2<int> spawnPos):Enemy(color, maxAP, 10/*HP*/,0/*init*/,false,GameCharacter::GCType::Melee ,{1,1},spawnPos){}//INSERIRE SKINPOS
//    };
//
//
//class Bat:public Enemy{
//    public:
//
//	void update(const float &deltaTime) override{};
//	void execute(Entity& e) override {}; 
//
//        Bat(sf::Texture &texture,int maxAP,int maxHP,int init,bool flying, sf::Vector2<int> spawnPos):Enemy(texture, maxAP, 8/*HP*/,5/*init*/,true,GameCharacter::GCType::Ranged ,{1,1},spawnPos){}//INSERIRE SKINPOS
//    };
//
//
//class Ranged:public Enemy{
//    public:
//
//	void update(const float &deltaTime) override{};
//	void execute(Entity& e) override {}; 
//
//        Ranged(sf::Texture &texture,int maxAP,int maxHP,int init,bool flying, sf::Vector2<int> spawnPos):Enemy(texture, maxAP, 5/*HP*/,3/*init*/ ,false,GameCharacter::GCType::Diglett,{1,1},spawnPos){}//INSERIRE SKINPOS
//    };


#endif //ENEMY_H

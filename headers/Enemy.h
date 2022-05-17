
#ifndef ENEMY_H
#define ENEMY_H

#include "GameCharacter.h"

class Enemy:public GameCharacter{
    public:
        bool canFly() override;
        Enemy(const sf::Color& color,PathAlgorithm &movementStrategy,int maxAP,int maxHP,int init,bool flying, sf::Vector2f skinPos, sf::Vector2<int> spawnPos):init(init), flying(flying), skinPos(skinPos),GameCharacter(color,movementStrategy, maxAP, maxHP,spawnPos){}
    private:
        int init;
        bool flying;
        sf::Vector2f skinPos;
        
};


class Melee:public Enemy{
    public:

	void update(const float &deltaTime) override{};
	void execute(Entity& e) override {}; 

        Melee(const sf::Color& color,PathAlgorithm &movementStrategy,int maxAP,int maxHP,int init,bool flying, sf::Vector2<int> spawnPos):Enemy(color,movementStrategy, maxAP, 10/*HP*/,0/*init*/,false ,{1,1},spawnPos){}//INSERIRE SKINPOS
    };


class Bat:public Enemy{
    public:

	void update(const float &deltaTime) override{};
	void execute(Entity& e) override {}; 

        Bat(const sf::Color& color,PathAlgorithm &movementStrategy,int maxAP,int maxHP,int init,bool flying, sf::Vector2<int> spawnPos):Enemy(color,movementStrategy, maxAP, 8/*HP*/,5/*init*/,true,{1,1},spawnPos){}//INSERIRE SKINPOS
    };


class Ranged:public Enemy{
    public:

	void update(const float &deltaTime) override{};
	void execute(Entity& e) override {}; 

        Ranged(const sf::Color& color,PathAlgorithm &movementStrategy,int maxAP,int maxHP,int init,bool flying, sf::Vector2<int> spawnPos):Enemy(color,movementStrategy, maxAP, 5/*HP*/,3/*init*/ ,false,{1,1},spawnPos){}//INSERIRE SKINPOS
    };



#endif //ENEMY_H

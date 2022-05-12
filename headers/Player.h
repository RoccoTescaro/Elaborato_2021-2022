

#ifndef PLAYER_H
#define PLAYER_H

#include "GameCharacter.h"

class Player:public GameCharacter{
    public:

	    void update(const float &deltaTime) override{};
    	void execute(Entity& e) override {}; 

        bool canFly() override;
        void foo();
        Player(PathAlgorithm &movementStrategy,sf::Texture &texture, int maxAP, int maxHP, sf::Vector2<int> spawnPos):AP(0),GameCharacter(movementStrategy,texture, maxAP, maxHP, spawnPos/*spawn pos*/){}
    private:
        int AP;
};


#endif //PLAYER_H




#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H
#include "Entity.h"
#include "Pathfinding.h"

class GameCharacter : public Entity {
public:
	virtual ~GameCharacter(){};
	GameCharacter (const sf::Color& color,PathAlgorithm &movementStrategy, int maxAP, int maxHP,sf::Vector2<int> pos):maxAP(maxAP), maxHP(maxHP), HP(maxHP),movementStrategy(movementStrategy), Entity(color,pos,{80,20},true) {
		sprite.setPosition(pos.x * cellDim.x, pos.y * cellDim.y);
		sprite.setSize(cellDim);
		sprite.setFillColor(sf::Color(0, 0, 255, 255));
	
	}
	virtual bool canFly()=0;
private:
	PathAlgorithm &movementStrategy;
	const int maxHP;
	int HP;
	const int maxAP;
	};


#endif //GAMECHARACTER_H

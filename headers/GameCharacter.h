


#include "Entity.h"
#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

class PathAlgorithm;

class GameCharacter : public Entity {
public:
	std::string serialize() {
		std::string a;
		a='a';
		return a;
	};
	virtual ~GameCharacter(){};
	GameCharacter (PathAlgorithm &movementStrategy,sf::Texture &texture, int maxAP, int maxHP,sf::Vector2<int> pos):maxAP(maxAP), maxHP(maxHP), HP(maxHP),movementStrategy(movementStrategy), Entity(pos,texture,{80,20},true) {
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

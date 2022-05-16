


#include "Entity.h"
#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H



class GameCharacter : public Entity {
public:
	enum class GCType{Player ='P',
				Melee ='M',
				Ranged ='R', 
				Diglett ='D', 
				Boss ='B'};
	virtual ~GameCharacter(){};
	GCType getGCType();
	GameCharacter (const sf::Color& color, int maxAP, int maxHP,GCType gcType,sf::Vector2<int> pos):maxAP(maxAP), maxHP(maxHP), HP(maxHP),gcType (gcType), Entity(color,{80,20}) {
		sprite.setPosition(pos.x * cellDim.x, pos.y * cellDim.y);
		sprite.setSize(cellDim);
		sprite.setFillColor(sf::Color(0, 0, 255, 255));
	
	}
	virtual bool canFly()=0;
private:
	const int maxHP;
	int HP;
	const int maxAP;
	const GCType gcType;
	};


#endif //GAMECHARACTER_H

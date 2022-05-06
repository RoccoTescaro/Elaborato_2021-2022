


#include "Entity.h"
#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H



class GameCharacter : public Entity {
public:
	enum GCType{Player ='P',
				Melee ='M',
				Ranged ='R', 
				Diglett ='D', 
				Boss ='B'};
	virtual ~GameCharacter(){};
	GCType getGCType();
	GameCharacter (sf::Texture &texture, int maxAP, int maxHP,GCType gcType):maxAP(maxAP), maxHP(maxHP), HP(maxHP),gcType (gcType), Entity(texture) {}
	virtual bool canFly()=0;
private:
	const int maxHP;
	int HP;
	const int maxAP;
	const GCType gcType;
	};


#endif //GAMECHARACTER_H

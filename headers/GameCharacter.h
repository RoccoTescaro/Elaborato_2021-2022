


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
	GameCharacter (sf::Texture &texture, int maxAP, int maxHP,GCType gcType):maxAP(maxAP), maxHP(maxHP), HP(maxHP),gcType (gcType), Entity(texture) {}
	private:
		const int maxHP;
		int HP;
		const int maxAP;
		GCType gcType;
	};


#endif //GAMECHARACTER_H

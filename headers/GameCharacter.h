


#include "Entity.h"
#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H



class GameCharacter : public Entity {
public:
	GameCharacter (sf::Texture &texture, int maxAP, int maxHP):maxAP(maxAP), maxHP(maxHP), HP(maxHP), Entity(texture) {}
	private:
		const int maxHP;
		int HP;
		const int maxAP;
	};


#endif //GAMECHARACTER_H

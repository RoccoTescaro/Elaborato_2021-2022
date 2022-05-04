


#include "Entity.h"
#ifndef UNTITLED_GAMECHARACTER_H
#define UNTITLED_GAMECHARACTER_H



class GameCharacter : public Entity {
public:
	GameCharacter (sf::Texture &texture, int maxActionPoints, int maxHP):maxActionPoints(maxActionPoints), maxHP(maxHP), HP(maxHP), Entity(texture) {}
	private:
		const int maxHP;
		int HP;
		const int maxActionPoints;
	};


#endif //UNTITLED_GAMECHARACTER_H

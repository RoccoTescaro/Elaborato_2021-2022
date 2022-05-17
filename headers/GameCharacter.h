#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "Entity.h"

class GameCharacter : public Entity {
public:
	GameCharacter(const sf::Vector2<float>& pos, const sf::Vector2<float>& size, uint8_t maxHealthPoints, uint8_t maxActionPoints) : 
		Entity(pos, size), maxHealthPoints(maxHealthPoints), maxActionPoints(maxActionPoints), hp(maxHealthPoints) {};
protected:
	const uint8_t maxHealthPoints;
	uint8_t hp;
	const uint8_t maxActionPoints;
	uint8_t ap = 0;
};


#endif //GAMECHARACTER_H

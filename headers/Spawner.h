#ifndef SPAWNER_H
#define SPAWNER_H

#include "Entity.h"
#include "GameCharacter.h"

template <class Type> //Type must be a GameCharacter but cant use it couse map cant append GameCharacter
class Spawner {
public:
	Spawner(const sf::Vector2<int>& pos, Map& map) : pos(pos), map(map) {};

	void update() {
		if (!gameCharacter)
		{
			map.append<Type>(pos);
			gameCharacter = map.get<Type>(pos);
		}
	};
private:
	sf::Vector2<int> pos;
	Map& map;
	GameCharacter* gameCharacter;
};

#endif //SPANWER_H

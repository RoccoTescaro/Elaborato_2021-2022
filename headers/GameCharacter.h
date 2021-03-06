#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "Entity.h"

class GameCharacter : public Entity {
public:
	GameCharacter(const sf::Vector2<int>& pos, const sf::Vector2<int>& size, uint8_t maxHealthPoints, uint8_t hp, uint8_t maxActionPoints, uint8_t ap, uint8_t initiative) :
		Entity(pos, size), maxHealthPoints(maxHealthPoints), hp(hp), maxActionPoints(maxActionPoints), ap(ap), initiative(initiative) {};

	uint8_t getInitiative() const;
protected:
	const uint8_t maxHealthPoints = 0;
	uint8_t hp;
	const uint8_t maxActionPoints = 0;
	uint8_t ap;

	const uint8_t initiative;
};

class Melee : public GameCharacter {
public:
    Melee(const sf::Vector2<int>& pos, const sf::Vector2<int>& size, uint8_t hp, uint8_t ap);

    void update(const float& dt) override {}; //#TODO
    void execute(Entity* entity) override {}; //#TODO

    std::string serialize() const override;
    static Entity* deserialize(std::string line);

    bool isSolid() const override;
private:

};

class Bat : public GameCharacter {
public:
    Bat(const sf::Vector2<int>& pos, const sf::Vector2<int>& size, uint8_t hp, uint8_t ap);

    void update(const float& dt) override {}; //#TODO
    void execute(Entity* entity) override {}; //#TODO

    std::string serialize() const override;
    static Entity* deserialize(std::string line);

    bool isSolid() const override;
private:

};

class Ranged : public GameCharacter {
public:
    Ranged(const sf::Vector2<int>& pos, const sf::Vector2<int>& size, uint8_t hp, uint8_t ap);

    void update(const float& dt) override {}; //#TODO
    void execute(Entity* entity) override {}; //#TODO

    std::string serialize() const override;
    static Entity* deserialize(std::string line);

    bool isSolid() const override;
private:

};

class Player : public GameCharacter {
public:
    Player(const sf::Vector2<int>& pos, const sf::Vector2<int>& size, uint8_t hp, uint8_t ap);

    void update(const float& dt) override {}; //#TODO
    void execute(Entity* entity) override {}; //#TODO

    std::string serialize() const override;
    static Entity* deserialize(std::string line);

    bool isSolid() const override;
private:

};


#endif //GAMECHARACTER_H

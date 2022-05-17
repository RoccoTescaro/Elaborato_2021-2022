#ifndef ENEMY_H
#define ENEMY_H

#include "GameCharacter.h"

class Enemy : public GameCharacter {
public:
    Enemy(const sf::Vector2<float>& pos, const sf::Vector2<float>& size, uint8_t maxHealthPoints, uint8_t maxActionPoints, uint8_t initiative) : 
        GameCharacter(pos, size, maxHealthPoints, maxActionPoints), initiative(initiative) {}
        
    uint8_t getInitiative() const;
protected:
    uint8_t initiative;        
};


class Melee : public Enemy {
public:
    Melee(const sf::Vector2<float>& pos, const sf::Vector2<float>& size);

	void update(const float& dt) override {}; //#TODO
	void execute(Entity* entity) override {}; //#TODO

    std::string serialize() const override;
    static Entity* deserialize(std::string line);

    bool isSolid() const override;
private:

};


class Bat : public Enemy {
public:
    Bat(const sf::Vector2<float>& pos, const sf::Vector2<float>& size);

    void update(const float& dt) override {}; //#TODO
    void execute(Entity* entity) override {}; //#TODO

    std::string serialize() const override;
    static Entity* deserialize(std::string line);

    bool isSolid() const override;
private:

};

class Ranged : public Enemy {
public:
    Ranged(const sf::Vector2<float>& pos, const sf::Vector2<float>& size);

    void update(const float& dt) override {}; //#TODO
    void execute(Entity* entity) override {}; //#TODO

    std::string serialize() const override;
    static Entity* deserialize(std::string line);

    bool isSolid() const override;
private:

};

#endif //ENEMY_H

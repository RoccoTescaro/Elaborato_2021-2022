#ifndef PLAYER_H
#define PLAYER_H

#include "GameCharacter.h"

class Player : public GameCharacter{
public:
    Player(const sf::Vector2<float>& pos, const sf::Vector2<float>& size);

    void update(const float& dt) override {}; //#TODO
    void execute(Entity* entity) override {}; //#TODO

    std::string serialize() const override;
    static Entity* deserialize(std::string line);

    bool isSolid() const override;
};


#endif //PLAYER_H

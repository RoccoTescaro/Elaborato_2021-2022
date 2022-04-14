#ifndef APPLICATION_H
#define APPLICATION_H
#include <SFML/Graphics.hpp>
#include "State.h"

class Application {
public:
    explicit Application(sf::Vector2<unsigned int> windowDim_);

    ~Application();

    void setState(State* state_);
private:
    State* state{};
    //Input input;
};

#endif //APPLICATION_H

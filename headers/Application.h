#ifndef APPLICATION_H
#define APPLICATION_H
#include <SFML/Graphics.hpp>
#include "State.h"

class Application {
public:
    Application(sf::Vector2<unsigned int> windowDim_);

    ~Application();

    void start();

    void setState(State* state);
private:
    State* state{};
    sf::RenderWindow window;
    //Input input;
};

#endif //APPLICATION_H

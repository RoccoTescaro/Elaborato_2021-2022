#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include "Input.h"
class Application;

class State {
public:
    State(Application* app_,sf::RenderWindow& window_,const float& dt_):app(app_),window(window_),dt(dt_){};
    virtual ~State() {};
    virtual void update() = 0;
    virtual void render() = 0;
protected:
    sf::RenderWindow& window;
    const float& dt;
    Input input{};
    Application* app;
};


#endif //STATE_H

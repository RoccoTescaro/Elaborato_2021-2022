#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
//#include "../headers/Input.h"
class Application;

class State {
public:
    State(Application* app_):app(app_){};
    virtual ~State() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
protected:
    //Input& input;
    Application* app;
};


#endif STATE_H

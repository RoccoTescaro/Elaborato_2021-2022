#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
//#include "../headers/Input.h"
class Application;

class State {
public:
    State(Application* app_):app(app_){};
    virtual ~State() {};
    virtual void update();
    virtual void render();
protected:
    //Input& input;
    Application* app;
};


#endif STATE_H

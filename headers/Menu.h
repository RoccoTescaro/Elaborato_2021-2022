#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Button.h"

class Menu : public State{
public:
    Menu(Application* app_,sf::RenderWindow& window_,const float& dt_);
    void update() override;
    void render() override;
private:
    sf::Text title;
    Button start;
    Button exit;
};


#endif //MENU_H

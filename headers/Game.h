#ifndef Game_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Map.h"

class Game : public State {
public:
    Game(Application* app_, sf::RenderWindow& window_, const float& dt_);
    void update() override;
    void render() override;
private:
    //WINDOW STUFF
    sf::View view;
    sf::View gui;
    const float viewZoomSpeed = 0.02f;
    float viewMovementSpeed;
    //MAP
    Map map;
    //MOUSE
    sf::Vector2<int> mousePos; //in map coordinates;
    sf::RectangleShape mouseIndicator;
};


#endif //Game_H

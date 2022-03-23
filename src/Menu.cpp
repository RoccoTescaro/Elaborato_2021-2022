#include "../headers/Menu.h"

Menu::Menu(Application* app_,sf::RenderWindow& window_,const float& dt_) : State(app_,window_,dt_){

}

void Menu::update() {
    State::update();
}

void Menu::render() {
    State::render();
}

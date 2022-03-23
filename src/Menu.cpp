#include <iostream>
#include "../headers/Menu.h"

Menu::Menu(Application* app_,sf::RenderWindow& window_,const float& dt_) :
State(app_,window_,dt_),
start(sf::Vector2<float>(0,window_.getSize().y*0.125*4),sf::Vector2<int>(window_.getSize().x,window_.getSize().y*0.125)),
exit(sf::Vector2<float>(0,window_.getSize().y*0.125*6),sf::Vector2<int>(window_.getSize().x,window_.getSize().y*0.125))
{
    titleFont.loadFromFile("../fonts/StintUltraCondensed-Regular.ttf");

    //TITLE
    title.setString("The Forbidden Sketchbook");
    title.setFont(titleFont);
    title.setCharacterSize(int(window.getSize().y*0.125));
    sf::FloatRect titleBound = title.getGlobalBounds(); //CENTER ALIGNMENT
    title.setPosition(window.getSize().x*0.5-titleBound.width*0.5,window.getSize().y*0.125-titleBound.height*0.5);

    //BUTTONS

}

void Menu::update() {

}

void Menu::render() {
    window.draw(title);
    start.render(window);
    exit.render(window);
}

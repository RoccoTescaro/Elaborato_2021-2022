//
// Created by lapo on 10/03/2022.
//

#include "../headers/Input.h"

const sf::Vector2f &Input::getMousePos() const {

    return MousePos;
}

bool Input::getKeyState(Input::keys key) {

    return KeyPressed[key];
}



void Input::updateKeys( sf::RenderWindow &window) {

    sf::Vector2i relativePos = sf::Mouse::getPosition(window);

    MousePos= window.mapPixelToCoords(relativePos);

    KeyPressed[Input::keys::W]=sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    KeyPressed[Input::keys::A]=sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    KeyPressed[Input::keys::S]=sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    KeyPressed[Input::keys::D]=sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    KeyPressed[Input::keys::MouseR]=sf::Mouse::isButtonPressed(sf::Mouse::Right);
    KeyPressed[Input::keys::MouseL]=sf::Mouse::isButtonPressed(sf::Mouse::Left);
    KeyPressed[Input::keys::Enter]=sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);


}


float Input::getWheelDelta() const {
    return WheelDelta;
}

void Input::updateWheelDelta(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::MouseWheelScrolled)
            WheelDelta=event.mouseWheelScroll.delta;
    }

}


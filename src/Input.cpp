//
// Created by lapo on 10/03/2022.
//

#include "Input.h"

const sf::Vector2f &Input::getMousePos() const {

    return MousePos;
}

bool Input::getKeyState(Input::keys key) {

    return KeyPressed[key];
}

void Input::updateKeys( sf::RenderWindow &window) {

    sf::Vector2i relativePos = sf::Mouse::getPosition(window);

    MousePos= window.mapPixelToCoords(relativePos);

    KeyPressed[0]=sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    KeyPressed[1]=sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    KeyPressed[2]=sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    KeyPressed[3]=sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    KeyPressed[4]=sf::Mouse::isButtonPressed(sf::Mouse::Right);
    KeyPressed[5]=sf::Mouse::isButtonPressed(sf::Mouse::Left);


}

Input::Input():WheelDelta(0) {
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


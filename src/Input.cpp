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



void Input::updateInputStatus( sf::RenderWindow &window) {

    sf::Vector2i relativePos = sf::Mouse::getPosition(window);

    MousePos= window.mapPixelToCoords(relativePos);

    KeyPressed[Input::keys::W]=sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    KeyPressed[Input::keys::A]=sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    KeyPressed[Input::keys::S]=sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    KeyPressed[Input::keys::D]=sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    KeyPressed[Input::keys::MouseR]=sf::Mouse::isButtonPressed(sf::Mouse::Right);
    KeyPressed[Input::keys::MouseL]=sf::Mouse::isButtonPressed(sf::Mouse::Left);
    KeyPressed[Input::keys::Enter]=sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);

    while (window.pollEvent(event))
    
    switch (event.type)
    {
        case sf::Event::MouseWheelScrolled:
            WheelDelta=event.mouseWheelScroll.delta;
            break;
        // window closed
        case sf::Event::Closed:
            window.close();
            break;
            
        default:
            break;
    }
}


float Input::getWheelDelta() const {
    return WheelDelta;
}



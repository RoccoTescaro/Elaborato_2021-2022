//
// Created by lapo on 10/03/2022.
//

#include "../headers/Input.h"
#include "../headers/Log.h"

void Input::update(sf::RenderWindow& window, const sf::View* view){
    //UPDATE MOUSE POS
    if (!view)
        view = &window.getDefaultView();

    mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window),*view);
     
    WheelDelta = 0.f;
    while (window.pollEvent(event)) { //handle Wheel changes but also other events
        if (event.type == sf::Event::Closed) window.close();
        else if (event.type == sf::Event::MouseWheelMoved)
            WheelDelta = event.mouseWheel.delta;
    }

    //UPDATE KEYS
    oldKeys = newKeys;
    newKeys[Key::W] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    newKeys[Key::A] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    newKeys[Key::S] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    newKeys[Key::D] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    newKeys[Key::MouseR] = sf::Mouse::isButtonPressed(sf::Mouse::Right);
    newKeys[Key::MouseL] = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    newKeys[Key::Enter] = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);

}

const sf::Vector2<float>& Input::getMousePos() const {
    return mousePos;
}

const float& Input::getWheelDelta() const {
    return WheelDelta;
}

bool Input::isKeyPressed(Input::Key key) const {
    return newKeys[key] && !oldKeys[key];
}

bool Input::isKeyDown(Input::Key key) const {
    return newKeys[key];
}

bool Input::isKeyReleased(Input::Key key) const {
    return !newKeys[key] && oldKeys[key];
}




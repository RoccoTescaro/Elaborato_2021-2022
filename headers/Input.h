//
// Created by lapo on 10/03/2022.
//
#include "SFML/Graphics.hpp"
#ifndef UNTITLED_INPUT_H
#define UNTITLED_INPUT_H


class Input {
public:

   enum keys  { W, A, S, D, MouseR, MouseL };

private:
///variables

    sf::Vector2f MousePos;//global position
    bool KeyPressed[6];//6= num. of input keys mapped                                                                                         //6 = keys(enum) length
    float WheelDelta;
public:
    Input();
///functions

            ///keys state output

    const sf::Vector2f &getMousePos() const;
    bool getKeyState(keys key);

    float getWheelDelta() const;

    ///keys state input
    void updateKeys(sf::RenderWindow& window);
    void updateWheelDelta(sf::RenderWindow& window);

};


#endif //UNTITLED_INPUT_H
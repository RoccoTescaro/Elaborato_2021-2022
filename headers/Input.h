//
// Created by lapo on 10/03/2022.
//
#ifndef INPUT_H
#define INPUT_H

#include "SFML/Graphics.hpp"
#include <bitset>

class Input {
public:
   enum Key 
   { 
       W, 
       A,
       S,
       D,
       MouseR,
       MouseL,
       Enter,
       ENUM_SIZE
   };

   void update(sf::RenderWindow& window, const sf::View* view = nullptr);

   const sf::Vector2<float>& getMousePos() const;
   const float& getWheelDelta() const;
   
   bool isKeyPressed(Key key) const;
   bool isKeyDown(Key key) const;
   bool isKeyReleased(Key key) const;

private:
    sf::Event event;
    sf::Vector2<float> mousePos;
    float WheelDelta = 0.f;
    std::bitset<Key::ENUM_SIZE> oldKeys;    //keys state on last update (used to handle key relase and key pressed function)                                                                               
    std::bitset<Key::ENUM_SIZE> newKeys;                                                                                                                                                                 
};


#endif //INPUT_H

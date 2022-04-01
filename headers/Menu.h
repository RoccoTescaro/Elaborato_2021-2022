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
    sf::Shader vignetteShader;
    sf::RectangleShape vignette;
    float vignetteRadius = 1.0f;
    const float vignetteRadiusOffset = .35f;
    const float vignetteRadiusAmplitude = .15f;
    bool switchScene = false;
    float time = 0;

    sf::Texture texBackground;

    sf::Sprite background;
    sf::Font titleFont;

    sf::Text title;
    sf::Font buttonFont;
    Button start;

    Button exit;
};


#endif //MENU_H

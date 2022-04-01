#include <iostream>
#include "../headers/Menu.h"

Menu::Menu(Application* app_,sf::RenderWindow& window_,const float& dt_) :
State(app_,window_,dt_),
start(sf::Vector2<float>(0,window_.getSize().y*0.125*4),sf::Vector2<int>(window_.getSize().x,window_.getSize().y*0.125)),
exit(sf::Vector2<float>(0,window_.getSize().y*0.125*6),sf::Vector2<int>(window_.getSize().x,window_.getSize().y*0.125))
{
    //BACKGROUND
    vignetteShader.loadFromFile("../shaders/vignette.frag",sf::Shader::Fragment);
    vignetteShader.setUniform("resolution",sf::Vector2f(window.getSize()));
    vignette.setSize(sf::Vector2f(window.getSize()));

    texBackground.loadFromFile("../images/paperBackground.jpg");
    background.setTexture(texBackground);
    background.setScale((float)window.getSize().x/texBackground.getSize().x,(float)window.getSize().x/texBackground.getSize().x);

    //FONTS
    titleFont.loadFromFile("../fonts/titleFont2.ttf");
    buttonFont.loadFromFile("../fonts/buttonFont1.ttf");

    //TITLE
    title.setFillColor(sf::Color(0,0,0,255));
    title.setString("The Forbidden Sketchbook");
    title.setFont(titleFont);
    title.setCharacterSize(int(window.getSize().y*0.125));
    sf::FloatRect titleBound = title.getGlobalBounds(); //CENTER ALIGNMENT
    title.setPosition(window.getSize().x*0.5-titleBound.width*0.5,window.getSize().y*0.125*2-titleBound.height*0.5);

    //BUTTONS
    start.setTextColor(sf::Color(0,0,0,255));
    exit.setTextColor(sf::Color(0,0,0,255));
    start.setText(" StaRt ");
    exit.setText(" ExiT ");
    start.setFont(buttonFont);
    exit.setFont(buttonFont);
    start.setTextSize(int(window.getSize().y*0.125));
    exit.setTextSize(int(window.getSize().y*0.125));
    sf::FloatRect startBound = start.getTextBound();
    sf::FloatRect exitBound = exit.getTextBound();
    start.setTextPos({window.getSize().x*0.5f-startBound.width*0.5f,window.getSize().y*0.125f*4-startBound.height*0.5f});
    exit.setTextPos({window.getSize().x*0.5f-exitBound.width*0.5f,window.getSize().y*0.125f*6-exitBound.height*0.5f});

}

void Menu::update() {
    time += dt;
    input.updateKeys(window);

    //UPDATE RENDERER
    if(start.isMouseOver(input.getMousePos())){
        start.setTextColor(sf::Color(255,255,255,255));
        if(input.getKeyState(input.MouseL)) start.setClicked(true);
    }
    else if(exit.isMouseOver(input.getMousePos())){
        exit.setTextColor(sf::Color(255,255,255,255));
        if(input.getKeyState(input.MouseL)) exit.setClicked(true);
    }else{
        start.setTextColor(sf::Color(0,0,0,255));
        exit.setTextColor(sf::Color(0,0,0,255));
    }

}

void Menu::render() {
    vignetteShader.setUniform("time",time);
    window.draw(background);
    window.draw(title);
    start.render(window);
    exit.render(window);
    window.draw(vignette,&vignetteShader);
}

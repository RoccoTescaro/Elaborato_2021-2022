#include <cmath>
#include "../headers/Application.h"
#include "../headers/Menu.h"
#include "../headers/Game.h"


Application::Application(sf::Vector2<unsigned int> windowDim_){
    sf::Clock clock;
    float dt = 0.0001;
    sf::RenderWindow window(sf::VideoMode(windowDim_.x,windowDim_.y),"",sf::Style::Titlebar);
    window.setFramerateLimit(60);
    state = new Menu(this, window, dt);
    sf::Event ev{};
    while(window.isOpen()){
        if(!state) return;
        state->update();
        window.clear();
        state->render();
        window.display();
        dt = fmax(clock.getElapsedTime().asSeconds(),0.0001);
        clock.restart();
    }
}

Application::~Application() {
    delete state;
}

void Application::setState(State* state_) {
    delete state;
    Application::state = state_;
}

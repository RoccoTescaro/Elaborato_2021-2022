#include "../headers/Application.h"
#include "../headers/Menu.h"


Application::Application(sf::Vector2<unsigned int> windowDim_){
    sf::Clock clock;
    float dt = 0.01;
    sf::RenderWindow window(sf::VideoMode(windowDim_.x,windowDim_.y),"",sf::Style::Titlebar);
    state = new Menu(this, window, dt);
    sf::Event ev{};
    while(window.isOpen()){
        if(!state) return;
        while(window.pollEvent(ev)) if(ev.type == sf::Event::Closed)window.close();
        state->update();
        window.clear();
        state->render();
        window.display();
        dt = clock.getElapsedTime().asSeconds();
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

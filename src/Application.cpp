#include "../headers/Application.h"

Application::Application(sf::Vector2<unsigned int> windowDim_){
    window.setSize(windowDim_);
    window.setTitle("");
}

Application::~Application() {
    delete state;
}

void Application::start() {
    while(window.isOpen()){
        if(!state) return;
        state->update();
        state->render();
    }
}

void Application::setState(State* state) {
    delete state;
    Application::state = state;
}

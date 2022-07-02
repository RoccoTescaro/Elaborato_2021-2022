#include "../headers/Game.h"

Game::Game(Application* app_, sf::RenderWindow& window_, const float& dt_) : State(app_, window_, dt_)
{
	map.load("maps/map.txt");

	mouseIndicator.setOutlineThickness(3);
	mouseIndicator.setSize(sf::Vector2<float>(map.getCellDim()));
	mouseIndicator.setFillColor(sf::Color(0, 0, 0, 0));
}

void Game::update()
{
	input.updateInputStatus(window);
	mousePos = map.worldCoordToPos(input.getMousePos());
	//map.update();
}

void Game::render()
{
	map.render(window);
	window.draw(mouseIndicator);
}

#include "../headers/Game.h"

Game::Game(Application* app_, sf::RenderWindow& window_, const float& dt_) : State(app_, window_, dt_)
{
	view.setCenter(window.getSize().x*0.5,window.getSize().y*0.5);
	view.setSize(window.getSize().x, window.getSize().y);
	gui = view; //same starting settings

	map.load("maps/map.txt");

	mouseIndicator.setOutlineThickness(3);
	mouseIndicator.setSize(sf::Vector2<float>(map.getCellDim()));
	mouseIndicator.setFillColor(sf::Color(0, 0, 0, 0));
}

void Game::update()
{
	//MOUSE
	input.updateInputStatus(window);
	mousePos = map.worldCoordToPos(input.getMousePos());
	mouseIndicator.setPosition(map.posToWorldCoord(mousePos));

	//VIEW
	view.zoom(1 - input.getWheelDelta() * viewZoomSpeed);
	view.move(
		(sf::Vector2<float>(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)) - sf::Vector2<float>(view.getCenter())).x * input.getWheelDelta() * viewZoomSpeed,
		(sf::Vector2<float>(window.mapPixelToCoords(sf::Mouse::getPosition(window), view)) - sf::Vector2<float>(view.getCenter())).y * input.getWheelDelta() * viewZoomSpeed
			  );

	viewMovementSpeed -= input.getWheelDelta() * 32.;

	int viewDirX = input.getKeyState(Input::keys::D) - input.getKeyState(Input::keys::A);
	int viewDirY = input.getKeyState(Input::keys::S) - input.getKeyState(Input::keys::W);

	view.setCenter(view.getCenter().x + viewDirX * viewMovementSpeed * dt , view.getCenter().y + viewDirY * viewMovementSpeed * dt);

	//map.update();
}

void Game::render()
{
	window.setView(view);
	map.render(window);
	window.draw(mouseIndicator);
	window.setView(gui);
}

#include "../headers/Camera.h"
#include "../headers/Log.h"

void Camera::update(const float& dt) {

	if (locked) return;

	sf::Vector2<float> dir(input.getKeyState(Input::D) - input.getKeyState(Input::A),
		input.getKeyState(Input::S) - input.getKeyState(Input::W));

	//NORMALIZE DIR
	float mod = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (mod > 0) {
		dir.x /= mod;
		dir.y /= mod;
	}

	view.setCenter(view.getCenter() + dir * movSpeed * dt);

	targetSize += sf::Vector2<float>{input.getWheelDelta(), input.getWheelDelta()* window.getSize().y / window.getSize().x}*zoomSpeed*dt;
	

	//SMOOTH ZOOM
	view.setSize(
				std::lerp(view.getSize().x,targetSize.x,dt),
				std::lerp(view.getSize().y,targetSize.y,dt)
				);

	window.setView(view);
}

void Camera::lock(bool condition) {
	locked = condition;
}
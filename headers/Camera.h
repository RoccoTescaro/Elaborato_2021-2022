#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Input.h"
#include "Log.h"

class Camera {
public:
	Camera(const sf::FloatRect& view_, sf::RenderWindow& window_, const Input& input_) : 
		view(view_), window(window_), input(input_), targetSize(view.getSize()) {};
	
	void update(const float& dt);

	void lock(bool condition);
private:

	sf::View view;
	sf::RenderWindow& window;
	const Input& input;

	bool locked = false;

	float movSpeed = 750; //dt ~= 0.01 sec -> pixel (x sec) ~= 750*0.01 = 7.5 

	sf::Vector2<float> targetSize;
	float zoomSpeed = 4000;
};

#endif //CAMERA_H
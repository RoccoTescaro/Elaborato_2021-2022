#include "../headers/Hud.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

Hud::Hud() {
	//HEALTH BAR
	healthBarTexture.loadFromFile("images/healthBar.png");
	healthBarFilterTexture.loadFromFile("images/healthBarFilter.png");
	healthBar.setTexture(healthBarTexture);
	healthBar.setPosition(16, 8);
	healthBar.setScale(0.25f, 0.25f);
	healthBarShader.loadFromFile("shaders/healthbar.frag", sf::Shader::Fragment);
	healthBarShader.setUniform("texture", healthBarTexture);
	healthBarShader.setUniform("filterTexture", healthBarFilterTexture);
	healthBarShader.setUniform("rect", sf::Glsl::Vec4(125., 285., 300., 1250.));
	healthBarShader.setUniform("resolution", sf::Glsl::Vec2(healthBarTexture.getSize().x,healthBarTexture.getSize().y));
	healthBarShader.setUniform("maxValue", 100.f);
	healthBarShader.setUniform("color", sf::Glsl::Vec4(0., 0., 0., 0.));
	healthBarShader.setUniform("replacedColor", sf::Glsl::Vec4(0.6, 0.05, 0.05, 1.));
	healthBarShader.setUniform("threshold", 0.22f);
}

void Hud::update(const float& dt) {
	float targetHp = 100.;
	float speed = 0.1;
	hp = std::lerp(hp,targetHp,speed*dt);
}

void Hud::render(sf::RenderWindow& window) {
	healthBarShader.setUniform("value", hp);
	window.draw(healthBar,&healthBarShader);
}
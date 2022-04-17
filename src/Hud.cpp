#include "../headers/Hud.h"
#include <cmath>

Hud::Hud() {
	//INK BAR
	inkBarTexture.loadFromFile("images/inkBar.png");
	inkBar.setTexture(inkBarTexture);
	inkBar.setPosition(16, 8);
	inkBar.setScale(0.5f, 0.5f);
	barShader.loadFromFile("shaders/bar.frag",sf::Shader::Fragment);
}

void Hud::update(const float& dt) {
	ink += 2.5*dt;
	if (ink > 100) ink = 100;
}

void Hud::render(sf::RenderWindow& window) {
	barShader.setUniform("texture", inkBarTexture);
	barShader.setUniform("xoffset", std::lerp(inkBar.getPosition().x+64.f,inkBar.getPosition().x+inkBar.getScale().x*inkBarTexture.getSize().x,ink/100.f));
	window.draw(inkBar,&barShader);
}
#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>


class Hud {
public:

	Hud();

	void update(const float& dt);

	void render(sf::RenderWindow& window);

private:

	//HEALTH BAR
	sf::Texture healthBarTexture;
	sf::Texture healthBarFilterTexture;
	sf::Sprite healthBar;
	sf::Shader healthBarShader;
	float hp = 0.; 

};



#endif //HUD_H
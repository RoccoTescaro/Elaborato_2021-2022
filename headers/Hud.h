#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>


class Hud {
public:

	Hud();

	void update(const float& dt);

	void render(sf::RenderWindow& window);

private:

	//INK BAR
	sf::Texture inkBarTexture;
	sf::Sprite inkBar;
	sf::Shader barShader;
	float ink = 0; //& (%)

};



#endif //HUD_H
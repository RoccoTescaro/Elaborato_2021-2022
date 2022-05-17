#include "../headers/Tile.h"
#include "../headers/Log.h"

bool Hole::isSolid(bool flying){
    if(flying){
        return false;
    }else{
        return solid;
    }
}


Entity* Wall::deserialize(std::string string) {
	//const sf::Color& color, sf::Vector2<int> pos, const sf::Vector2<float>& cellDim
	//12094 Wall 125 200 0 12 11 48.f 48.f
	std::string str = string.substr(0,string.find(" "));
	uint8_t r = std::stoi(str);
	string.erase(0,string.find(" ")+1);
	str = string.substr(0 , string.find(" "));
	uint8_t g = std::stoi(str);
	string.erase(0, string.find(" ") + 1);
	str = string.substr(0, string.find(" "));
	uint8_t b = std::stoi(str);
	string.erase(0, string.find(" ") + 1);
	str = string.substr(0, string.find(" "));
	int x = std::stol(str);
	string.erase(0, string.find(" ") + 1);
	str = string.substr(0, string.find(" "));
	int y = std::stol(str);
	string.erase(0, string.find(" ") + 1);
	str = string.substr(0, string.find(" "));
	float cellX = std::stof(str);
	string.erase(0, string.find(" ") + 1);
	str = string.substr(0, string.find(" "));
	float cellY = stof(str);
	return new Wall(sf::Color{ r,g,b }, sf::Vector2<int>{ x,y }, sf::Vector2<float>{ cellX,cellY });
}

std::string Wall::serialize() {
	std::string string;
	string += "Wall ";
	string += std::to_string(sprite.getFillColor().r) + " ";
	string += std::to_string(sprite.getFillColor().g) + " ";
	string += std::to_string(sprite.getFillColor().b) + " ";
	string += std::to_string(int(sprite.getPosition().x/cellDim.x)) + " ";
	string += std::to_string(int(sprite.getPosition().y/cellDim.y)) + " ";
	string += std::to_string(cellDim.x) + " ";
	string += std::to_string(cellDim.y);
	DEBUG(("Wall serialized: "+string).c_str());
	return string;
}
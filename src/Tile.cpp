#include "../headers/Tile.h"
#include "../headers/Log.h"

<<<<<<< HEAD
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
=======
///////////////////////////WALL//////////////////////////

Wall::Wall(const sf::Vector2<float>& pos, const sf::Vector2<float>& size) : Tile(pos, size) {
	testingSprite.setFillColor({ 128, 0, 255, 64 });
>>>>>>> Map
}

std::string Wall::serialize() const {
	return "Wall {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "}";
}

Entity* Wall::deserialize(std::string line) {
	std::vector<std::string> parameters;
	parseString(parameters, line);
	
	float posX = std::stof(parameters[0]);
	float posY = std::stof(parameters[1]);
	float sizeX = std::stof(parameters[2]);
	float sizeY = std::stof(parameters[3]);
	return new Wall({ posX,posY }, { sizeX,sizeY });
}

bool Wall::isSolid() const{
	return true;
}

///////////////////////////HOLE//////////////////////////

Hole::Hole(const sf::Vector2<float>& pos, const sf::Vector2<float>& size) : Tile(pos, size) {
	testingSprite.setFillColor({ 10, 0, 40, 64 });
}

std::string Hole::serialize() const {
	return "Hole {" +
		std::to_string(testingSprite.getPosition().x) + "," +
		std::to_string(testingSprite.getPosition().y) + "," +
		std::to_string(testingSprite.getSize().x) + "," +
		std::to_string(testingSprite.getSize().y) + "}";
}

Entity* Hole::deserialize(std::string line) {
	std::vector<std::string> parameters;
	parseString(parameters, line);

	float posX = std::stof(parameters[0]);
	float posY = std::stof(parameters[1]);
	float sizeX = std::stof(parameters[2]);
	float sizeY = std::stof(parameters[3]);
	return new Hole({ posX,posY }, { sizeX,sizeY });
}

bool Hole::isSolid() const {
	return false;
}
#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <unordered_map>


class Entity {
public:
	Entity(const sf::Vector2<float>& cellDim_) : cellDim(cellDim_) {}
	virtual ~Entity() {}
	void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}

	void move(const sf::Vector2<int>& pos) {
		sprite.setPosition(pos.x * cellDim.x, pos.y * cellDim.y);
	}

	virtual std::string serialize() {}
	virtual Entity* deserialize(const std::string& string_) {}

protected:
	const sf::Vector2<float>& cellDim;
	sf::RectangleShape sprite;
};


class Tile : public Entity {
public:
	Tile(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim) : Entity(cellDim) {
		sprite.setPosition(pos.x * cellDim.x, pos.y * cellDim.y);
		sprite.setSize(cellDim);
	}
};
class GameCharacter : public Entity {
public:
	GameCharacter(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim) : Entity(cellDim) {
		sprite.setPosition(pos.x * cellDim.x, pos.y * cellDim.y);
		sprite.setSize(cellDim);
		sprite.setFillColor(sf::Color(0, 0, 255, 255));
	}
};
class Wall : public Tile {
public:
	Wall(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim) : Tile(pos, cellDim) {
		sprite.setFillColor(sf::Color(255, 0, 0, 255));
	}
};
class Hole : public Tile {
public:
	Hole(sf::Vector2<int> pos, const sf::Vector2<float>& cellDim) : Tile(pos, cellDim) {
		sprite.setFillColor(sf::Color(0, 255, 0, 255));
	}
};

class Map {
public:
	enum class entityLayer { tileLayer, gameCharacterLayer, any};

	void appendEntity(float x, float y, Entity* entity); // not really wanna use template but i could
	void appendEntity(int x, int y, Entity* entity);
	void appendEntity(const sf::Vector2<float>& pos, Entity* entity);
	void appendEntity(const sf::Vector2<int>& pos, Entity* entity);

	void removeEntity(float x, float y, Map::entityLayer layer = entityLayer::any);
	void removeEntity(int x, int y, Map::entityLayer layer = entityLayer::any);
	void removeEntity(const sf::Vector2<float>& pos, Map::entityLayer layer = entityLayer::any);
	void removeEntity(const sf::Vector2<int>& pos, Map::entityLayer layer = entityLayer::any);

	Entity* operator()(float x, float y, Map::entityLayer layer = entityLayer::any); //getEntity with any as layer prioritize gameCharacter
	Entity* operator()(int x, int y, Map::entityLayer layer = entityLayer::any);
	Entity* operator()(const sf::Vector2<float>& pos, Map::entityLayer layer = entityLayer::any);
	Entity* operator()(const sf::Vector2<int>& pos, Map::entityLayer layer = entityLayer::any);
	Entity* getEntity(float x, float y, Map::entityLayer layer = entityLayer::any);
	Entity* getEntity(int x, int y, Map::entityLayer layer = entityLayer::any);
	Entity* getEntity(const sf::Vector2<float>& pos, Map::entityLayer layer = entityLayer::any);
	Entity* getEntity(const sf::Vector2<int>& pos, Map::entityLayer layer = entityLayer::any);

	sf::Vector2<int> indexToPos(uint32_t index);
	uint32_t posToIndex(float x, float y);
	uint32_t posToIndex(int x, int y);
	uint32_t posToIndex(const sf::Vector2<float>& pos);
	uint32_t posToIndex(const sf::Vector2<int>& pos);

	void load(std::fstream& file); //#TODO
	void save(std::fstream& file); //#TODO

	void render(sf::RenderWindow& window);

	void move(const sf::Vector2<int>& start, const sf::Vector2<int>& end); //only for GameCharacters

	const sf::Vector2<int>& getDim() const;
	const sf::Vector2<float>& getCellDim() const;

	template<typename T> static void registerType();
private:
	void appendEntity(uint32_t index, Entity* entity);
	void removeEntity(uint32_t index, Map::entityLayer layer = entityLayer::any);
	Entity* getEntity(uint32_t index, Map::entityLayer layer = entityLayer::any);
	
	static std::unordered_map<const char*, Entity* (*)(const std::string&)>* getRegister();

	std::unordered_map<uint32_t, std::unique_ptr<Tile>> tiles;
	std::unordered_map<uint32_t, std::unique_ptr<GameCharacter>> gameCharacters;

	sf::Vector2<int> dim;
	const sf::Vector2<float> cellDim{ 48.f, 48.f }; //#TODO float or int?
};


template<typename T>
void Map::registerType() {
	getRegister()->insert(std::make_pair(typeid(T).name(),&T.deserialize)); //#TODO test T.deserialize
}



#endif //MAP_H
//TODO: add inventory
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System/Vector2.hpp>

#include "Ini.hpp"
#include "resources.hpp"
#include "tools.hpp"
//TODO: Problem with World.hpp

class Player {
public:
	Player(uint, uint);
	~Player();

	enum Side {Up = 0, Down, Left, Right};

	sf::Vector2f getPosition(void);
	sf::Vector2f getPosition64(void);

	uint getV(void);

	void draw(sf::RenderWindow &window);

	bool collision();
	void move(Side);
	void update();

	void load(const std::string name);
	void save(const std::string name);

private:
	uint posX = 0, posY = 0;
	uint v = 32;

	sf::Texture playerT;
	sf::Sprite player;

	Ini iniFile;
};

#endif // PLAYER_HPP

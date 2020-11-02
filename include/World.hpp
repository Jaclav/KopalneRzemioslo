//TODO: dodać itemy na ziemi jako vector
//TODO: dodać struktury
#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>

#ifdef _WIN32
#include <dir.h>
#endif // _WIN32

#include <SFML/System/Vector2.hpp>

#include "tools.hpp"
#include "Console.hpp"//must be after tools.hpp
#include "Ini.hpp"
#include "Items.hpp"
#include "version.hpp"

extern int usingSystem;

class World {
public:
	World();
	~World();

	Items::Item& operator () (uint r, uint c);

	sf::Vector2u getSize(void);

	std::string getName(void);
	bool getNoclip(void);

	void setName(std::string);

	void generate(void);
	void save(void);
	void load(void);
	void reset(void);

private:
	static const uint sizeX = 2000, sizeY = 255;
	Items::Item map[sizeX][sizeY];

	bool allowCommands = 1, noclip = false;
	uint seed;
	std::string name;

	std::fstream file;

	Console console;
	Ini iniFile;

	friend class Menu;//TODO: friend function, not classs
};

#endif // WORLD_HPP

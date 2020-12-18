//TODO: add structures
//TODO: add resizing
#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <vector>

#ifdef _WIN32
#include <dir.h>
#endif // _WIN32

#include <SFML/System/Vector2.hpp>

#include "Console.hpp"
#include "Ini.hpp"
#include "Items.hpp"
#include "tools.hpp"
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

    bool allowCommands = 1, noclip = false;

private:
    static const uint sizeX = 2000, sizeY = 255;
    Items::Item map[sizeX][sizeY];

    uint seed;
    std::string name;

    std::fstream file;

    Console console;
    Ini iniFile;

    friend class Menu;//TODO: friend function, not classs
};

#endif // WORLD_HPP

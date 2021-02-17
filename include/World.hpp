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

    bool getAllowCommands(void);
    std::string getName(void);
    bool getNoclip(void);
    sf::Vector2u getSize(void);

    void setAllowCommands(bool);
    void setName(std::string);
    void setNoclip(bool);

    void generate(void);
    void save(void);
    void load(void);
    void reset(void);

private:
    bool allowCommands = 1, noclip = false;
    static const uint sizeX = 2000, sizeY = 255;
    Items::Item map[sizeX][sizeY];

    uint seed;
    std::string name;

    std::fstream file;

    Console console;
    Ini iniFile;
};

#endif // WORLD_HPP

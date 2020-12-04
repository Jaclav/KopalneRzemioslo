//TODO: add physics
//TODO: when player does not see, don't draw
//TODO:file operations
#ifndef DROPPED_HPP
#define DROPPED_HPP

#include <iostream>

#include "Items.hpp"

class Dropped{
public:
    Dropped();
    ~Dropped();

    struct Plurality{
        Items::Item type;
        uint quantity;
    };
    void draw(sf::RenderWindow & window);

    //operations on dropped items
    void drop(uint x, uint y, Items::Item t, uint q);
    Plurality collect(uint x, uint y);

    //file operations
    //void load(const std::string name);
    //void save(const std::string name);

private:
    std::vector<uint>posX;
    std::vector<uint>posY;
    std::vector<Items::Item>type;
    std::vector<uint>quantity;

    Items* items;
};

#endif // DROPPED_HPP

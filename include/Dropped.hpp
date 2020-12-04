//TODO: add physics
#ifndef DROPPED_HPP
#define DROPPED_HPP

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

private:
    std::vector<uint>posX;
    std::vector<uint>posY;
    std::vector<Items::Item>type;
    std::vector<uint>quantity;

    Items* items;
};

#endif // DROPPED_HPP

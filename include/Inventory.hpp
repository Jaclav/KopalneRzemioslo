#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <SFML/Graphics.hpp>

#include "Ini.hpp"
#include "Items.hpp"
#include "resources.hpp"

extern sf::Font font;

class Inventory {
public:
    Inventory();
    ~Inventory();

    Items::Item getTypeOfCurrentItem(void);

    void setPtr(uchar where);
    void incPtr(void);
    void decPtr(void);

    bool add(Items::Item);
    Items::Item remove();

    void draw(sf::RenderWindow &window);

    void load(std::string name);
    void save(std::string name);

private:
    Items::Item typeOfItems[10] = {Items::Air, Items::Air, Items::Air, Items::Air, Items::Air, Items::Air, Items::Air, Items::Air, Items::Air, Items::Air};
    uchar numberOfItems[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uchar ptr = 0;

    Items* items;

    sf::Text number;

    sf::Texture barT;
    sf::Sprite bar;

    sf::Texture currentItemT;
    sf::Sprite currentItem;

    Ini iniFile;
};

#endif // INVENTORY_HPP

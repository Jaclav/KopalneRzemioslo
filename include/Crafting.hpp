//TODO: when player does not see, don't draw
#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include <SFML/Graphics.hpp>

#include "Items.hpp"

class Crafting {
public:
    Crafting(sf::RenderWindow &window);
    ~Crafting();

    void draw(sf::RenderWindow &window);
    bool getShowing(void);
    void setShowing(bool onWhat);

private:
    bool isShowing = false;
    Items::Item table[3][3];

    sf::RectangleShape background;
};

#endif // CRAFTING_HPP

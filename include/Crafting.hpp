#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include <SFML/Graphics.hpp>

#include "Items.hpp"
#include "Player.hpp"

class Crafting {
public:
    Crafting(sf::RenderWindow &window, Player &player);
    ~Crafting();

    void draw(sf::RenderWindow &window);
    bool getShowing(void);
    void setShowing(bool onWhat);

private:
    bool isShowing = false;
    Items::Item table[3][3];

    Player *player;

    sf::RectangleShape background;
};

#endif // CRAFTING_HPP

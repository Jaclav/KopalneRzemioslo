#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "Items.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "World.hpp"

extern sf::Font font;

class Game {
public:
    Game(sf::RenderWindow & window, World &);
    ~Game();

    enum Returned {Quit = 0, Back};

    Returned play(Menu &menu);

private:
    sf::RenderWindow *window;
    sf::View view;
    sf::Event event;

    Items *items;
    World *world;

    bool showDebug = false;

    Menu::Returned returned;
};

#endif // GAME_HPP

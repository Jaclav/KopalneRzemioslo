#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "Crafting.hpp"
#include "Dropped.hpp"
#include "Items.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "../resources/backgrounds/mntBackground.hpp"
#include "../resources/sounds/digging.hpp"
#include "../resources/sounds/putting.hpp"
#include "../resources/textures.hpp"
#include "World.hpp"

extern sf::Font font;

class Game {
public:
    Game(sf::RenderWindow & window, World &);
    ~Game();

    enum Returned {Quit = 0, Back};
    Returned play(Menu &menu);

private:
    //SFML
    sf::RenderWindow *window;
    sf::View view;
    sf::Event event;

    //engine
    Dropped dropped;
    Dropped::Plurality plr;
    Items items;
    World *world;

    Crafting* crafting;//TODO: make it not pointer
    Player *player;//TODO: make it not pointer

    //resources
    Animation breaking;
    bool canBreak = false;
    sf::Vector2i breakingMousePos;

    sf::Texture mntBackgroundT;
    sf::Sprite mntBackground;

    sf::SoundBuffer diggingB;
    sf::Sound digging;

    sf::SoundBuffer puttingB;
    sf::Sound putting;

    //console
    void interpreter(void);
    bool showConsole = false;
    std::string command, commandInfo;
    sf::RectangleShape consoleBackground;
    sf::Text consoleText;

    //other
    bool showDebug = false;
    bool wasEscapeReleased = true;
    Menu::Returned returned;
};

#endif // GAME_HPP

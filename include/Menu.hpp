#ifndef MENU_HPP
#define MENU_HPP

#include <dirent.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Button.hpp"
#include "resources.hpp"
#include "tools.hpp"
#include "version.hpp"
#include "World.hpp"

extern sf::Font font;
extern bool soundOption;

class Menu {
public:
    Menu(sf::RenderWindow &_window);
    ~Menu();

    enum Returned {Quit = 0, Back, Info, Options, Play, Save, SaveAndExit, DontSave, LoadWorld, NewWorld};

    Returned info(void);
    Returned options(void);
    Returned pause(void);
    Returned play(World &world);//TODO: do better list of worlds
    Returned start(void);

private:
    sf::RenderWindow* window;
    sf::Event event;

    sf::SoundBuffer themeB;
    sf::Sound theme;

    sf::Texture dirtBackgroundT;
    sf::Sprite dirtBackground;

    sf::Texture startBackgroundT;
    sf::Sprite startBackground;

    sf::Text mainText;

    Button button1;
    Button button2;
    Button button3;
    Button button4;

    sf::Vector2u windowSize;
    sf::Vector2u halfOfWindowSize;

    sf::Clock clock;
    bool animationPage;

    inline void playTheme(void);
};

#endif // MENU_HPP

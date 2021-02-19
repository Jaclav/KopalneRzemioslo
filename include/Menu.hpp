#ifndef MENU_HPP
#define MENU_HPP

#include <algorithm>
#include <dirent.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#ifdef _WIN32
#include <dir.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif // _WIN32

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
    Returned play(World &world);
    Returned start(void);

private:
    sf::RenderWindow *window;
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
    Button button5;

    sf::Vector2u windowSize;
    sf::Vector2u halfOfWindowSize;

    sf::Clock clock;
    bool animationPage;

    inline void playTheme(void);
};

#endif // MENU_HPP

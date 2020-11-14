////////////////////////////////////////
//
// KopalneRzemiosło
// Copyright (C) 2020 Jacek 'Dobromir'
// Napisane dzięki koronarferiom.
// Pisane od 24.05.2020 do
//
////////////////////////////////////////
//TODO:////////////////////////////////////
//- dodać listę itemów leżących na ziemi i dodać jej zapis do .ini
//- crafting, drabiny, drzwi, ściany, tła
//- rudy, złoża
//- dzień/noc, światło, raytraycing
//- woda, lawa, ogień
//- zwierzęta
//- przeciwnicy(agresywne zwierzęta)
//- Biomy
//- aktualizacje związane z biomami
//- multiplayer
////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#ifdef _WIN32
#include <windows.h>
HWND windowHandle;
#endif // _WIN32

#include "Console.hpp"
#include "Game.hpp"
#include "Ini.hpp"
#include "Menu.hpp"
#include "resources.hpp"
#include "tools.hpp"
#include "version.hpp"
#include "World.hpp"

sf::Font font;
bool soundOption;
int usingSystem;

int main() {
#ifdef _WIN32
    DeleteFile("debug.log");
#else
    usingSystem = system("rm debug.log 2> /dev/null");
#endif // _WIN32
    Console console;
    console.log("Starting version: " + std::string(version) + " compilation: " + std::string(__DATE__) + " - " + std::string(__TIME__));

    World world;

    //opening window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Kopalne Rzemioslo", sf::Style::Fullscreen);
#ifdef _WIN32
    windowHandle = window.getSystemHandle();
#endif // _WIN32
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    //setting cursor
    sf::Image mainCursor;
    if(!mainCursor.loadFromMemory(cursor_png, cursor_png_len))
        exit(1);
    sf::Cursor cursor;
    if(cursor.loadFromPixels(mainCursor.getPixelsPtr(), mainCursor.getSize(), sf::Vector2u(0, 0)))
        window.setMouseCursor(cursor);
    else
        console.error("Failed to load cursor from image.");

    //loading global font
    if(!font.loadFromMemory(BlueHighwayPixielated_G8Mm_ttf, BlueHighwayPixielated_G8Mm_ttf_len))
        exit(-1);

    //loading soundOption
    Ini optionsIni("game.ini");
    soundOption = optionsIni.readInt("options", "sound", true);

    //menu
    Menu menu(window);
    Menu::Returned returned;

    //game
    Game game(window, world);

    while(true) {
        returned = menu.start();

        if(returned == Menu::Quit) {
            break;
        }
        else if(returned == Menu::Info) {
            if(menu.info() == Menu::Quit) {
                break;
            }
        }
        else if(returned == Menu::Options) {
            returned = menu.options();

            if(returned == Menu::Save) {
                optionsIni.writeInt("options", "sound", soundOption);//save current
            }
            else if(returned == Menu::DontSave) {
                soundOption = optionsIni.readInt("options", "sound", true);
            }
            else { //Menu::Quit
                break;
            }
        }
        else if(returned == Menu::Play) {
            returned = menu.play(world);

            if(returned == Menu::LoadWorld) {
                world.load();
            }
            else if(returned == Menu::NewWorld) {
                world.generate();
                world.save();
            }
            else if(returned == Menu::Quit) {
                break;
            }
            else if(returned == Menu::Back) {
                continue;
            }

            if(game.play(menu) == Game::Quit ) {
                break;
            }
        }
    }

    console.log("Program end.");
    return 0;
}

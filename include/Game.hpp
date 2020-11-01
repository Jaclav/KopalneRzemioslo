#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "Items.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "resources.hpp"
#include "World.hpp"

extern sf::Font font;

class Game {
public:
	Game(sf::RenderWindow & window, World &);
	~Game();

	enum Returned {Quit = 0, Back};

	Returned play(Menu &menu);
	void console(std::string command);

private:
	sf::RenderWindow *window;
	sf::View view;
	sf::Event event;

	Items *items;
	World *world;

	sf::SoundBuffer diggingB;
	sf::Sound digging;

	sf::SoundBuffer puttingB;
	sf::Sound putting;

	bool showDebug = false;
	bool showConsole = false;

	Menu::Returned returned;
};

#endif // GAME_HPP

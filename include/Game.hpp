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

private:
	sf::RenderWindow *window;
	sf::View view;
	sf::Event event;

	Items *items;
	World *world;

	Player player;

	sf::SoundBuffer diggingB;
	sf::Sound digging;

	sf::SoundBuffer puttingB;
	sf::Sound putting;

	bool showDebug = false;

	void interpreter(void);
	bool showConsole = false;
	std::string command, commandInfo;
	sf::RectangleShape consoleBackground;
	sf::Text consoleText;

	Menu::Returned returned;
};

#endif // GAME_HPP

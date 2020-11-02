#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Mouse.hpp>
#include "resources.hpp"
#include "tools.hpp"

extern sf::Font font;
extern bool soundOption;

class Button {
public:
	Button(float x = 0, float y = 0, float width = 300, float height = 100, const std::string string = "Text");

	void create(float x = 0, float y = 0, float width = 300, float height = 100, const std::string string = "Text");

	void setStrig(std::string string);
	void draw(sf::RenderWindow& window);
	bool isCovering(void);

private:
	sf::Text text;

	sf::RectangleShape button;
	sf::RectangleShape shadow;

	sf::SoundBuffer soundB;
	sf::Sound sound;
	bool playsound = true;
};

#endif // BUTTON_HPP

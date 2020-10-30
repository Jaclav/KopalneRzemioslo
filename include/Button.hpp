#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Mouse.hpp>
#include "resources.hpp"
#include "tools.hpp"

extern sf::Font font;
extern bool soundOption;

static const sf::String shaderStr = "\
void main(){\
	gl_FragColor=vec4(0,0,1,0.5);\
}";//dzięki static widoczne tylko w button.hpp i button.cpp

class Button {
public:
    Button(float x = 0, float y = 0, float width = 300, float height = 100, const sf::String string = "Text");

    void setStrig(sf::String string);
    void draw(sf::RenderWindow& window);
    bool isCovering(void);

private:
    sf::Shader shader;
    bool displayShader;

    sf::Text text;

    sf::RectangleShape button;
    sf::RectangleShape shadow;

    sf::SoundBuffer soundB;
    sf::Sound sound;
    bool playsound = true;
};

#endif // BUTTON_HPP

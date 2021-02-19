#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#ifdef _WIN32
#include <windows.h>
extern HWND windowHandle;
#endif // _WIN32

extern sf::Font font;
extern int systemStatus;

typedef unsigned int uint;
typedef unsigned char uchar;

uchar fpsCounter(void);
bool isCovering(uint x1, uint y1, uint x2, uint y2, uint width2, uint height2);
bool isMouseCoveringShape(sf::Shape &shape);
void printScreen(sf::RenderWindow &window);

class TextInput {
public:
    enum Type {Number, Text};
    TextInput(uint posX, uint posY, uint sizeX, uint sizeY, Type type);
    ~TextInput();
    void draw(sf::RenderWindow &window);
    void input(sf::Event event);

    std::string getString(void);
private:
    sf::RectangleShape background;
    bool inFocus = false;
    sf::Text text;
    Type type;
};

#endif // TOOLS_HPP

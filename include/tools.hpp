#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#ifdef _WIN32
#include <windows.h>
extern HWND windowHandle;
#endif // _WIN32

extern int usingSystem;

typedef unsigned int uint;
typedef unsigned char uchar;

void printScreen(sf::RenderWindow &window);
bool isMouseCoveringShape(sf::Shape &shape);

#endif // TOOLS_HPP

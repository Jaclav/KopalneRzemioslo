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

uchar fpsCounter(void);
bool isCovering(uint x1, uint y1, uint x2, uint y2, uint width2, uint height2);
bool isMouseCoveringShape(sf::Shape &shape);
void printScreen(sf::RenderWindow &window);

#endif // TOOLS_HPP

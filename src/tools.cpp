#include "tools.hpp"

void printScreen(sf::RenderWindow &window) {
    //print screen
    sf::Texture prtscr;

    prtscr.create(window.getSize().x, window.getSize().y);
    prtscr.update(window);
#ifdef _WIN32
    prtscr.copyToImage().saveToFile("%Temp%\\kr_screenshot.png");
    if(!system("explorer %Temp%\\kr_screenshot.png")) {
        ShowWindow(windowHandle, SW_MINIMIZE);
        MessageBox(NULL, "Failed to take a screenshot", "Warning", MB_DEFAULT_DESKTOP_ONLY | MB_ICONWARNING | MB_TOPMOST);
    }

#elif defined __linux__ || defined linux || defined __linux
    prtscr.copyToImage().saveToFile("/tmp/kr_screenshot.png");
    if(system("thunar /tmp/kr_screenshot.png") != 0) {
        system("zenity --warning --text=\"Failed to take a screenshot.\" --title=\"Warning!\"&");
    }
#else
#error Unknown OS
#endif // _WIN32
    return;
}

bool isMouseCoveringShape(sf::Shape &shape) {
    if(sf::Mouse::getPosition().x >= shape.getPosition().x &&
            sf::Mouse::getPosition().x <= shape.getPosition().x + shape.getLocalBounds().width &&
            sf::Mouse::getPosition().y >= shape.getPosition().y &&
            sf::Mouse::getPosition().y <= shape.getPosition().y + shape.getLocalBounds().height) {
        return true;
    }
    else {
        return false;
    }
}


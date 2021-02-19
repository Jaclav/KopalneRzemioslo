#include "tools.hpp"

uchar fpsCounter(void) {
    static uchar fps, oldfps;
    static sf::Clock clck;

    if(clck.getElapsedTime().asMilliseconds() >= 1000) {
        oldfps = fps;
        fps = 0;
        clck.restart();
    }
    else {
        fps++;
    }
    return oldfps;
}

bool isCovering(uint x1, uint y1, uint x2, uint y2, uint width2, uint height2) {
    if(x1 > x2 && x1 < x2 + width2 && y1 > y2 && y1 < y2 + height2) {
        return true;
    }
    return false;
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

void printScreen(sf::RenderWindow &window) {
    //print screen
    sf::Texture prtscr;

    prtscr.create(window.getSize().x, window.getSize().y);
    prtscr.update(window);
#ifdef _WIN32
    if(!prtscr.copyToImage().saveToFile(std::string(getenv("Temp")) + "\\kr_screenshot.png")) {
        ShowWindow(windowHandle, SW_MINIMIZE);
        MessageBox(NULL, "Failed to take a screenshot", "Warning", MB_DEFAULT_DESKTOP_ONLY | MB_ICONWARNING | MB_TOPMOST);
        return;
    }
    system("explorer %Temp%\\kr_screenshot.png");
#elif defined __linux__ || defined linux || defined __linux
    if(!prtscr.copyToImage().saveToFile("/tmp/kr_screenshot.png")) {
        usingSystem = system("zenity --warning --text=\"Failed to take a screenshot.\" --title=\"Warning!\"&");
        return;
    }
    usingSystem = system("xdg-open /tmp/kr_screenshot.png");
#else
#error Unknown OS
#endif // _WIN32
    return;
}

TextInput::TextInput(uint posX, uint posY, uint sizeX, uint sizeY, Type type) : text("", font, 40) {
    this->type = type;
    background.setSize(sf::Vector2f(sizeX, sizeY));
    background.setPosition(posX, posY);
    background.setFillColor(sf::Color(48, 26, 0, 200));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(2);

    text.setPosition(background.getPosition().x + 10, background.getPosition().y + text.getCharacterSize() / 2.5);
}
TextInput::~TextInput() {
    //dtor
}
void TextInput::draw(sf::RenderWindow &window) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(isMouseCoveringShape(background))
            inFocus = true;
        else
            inFocus = false;
    }
    window.draw(background);
    window.draw(text);
}
void TextInput::input(sf::Event event) {
    if(!inFocus)
        return;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
        text.setString(text.getString().substring(0, text.getString().getSize() - 1));
    }
    else if(type == Type::Text) {
        text.setString(text.getString() + event.text.unicode);
    }
    else if(type == Type::Number && event.text.unicode > 47 && event.text.unicode < 58) {
        text.setString(text.getString() + event.text.unicode);
    }
}

std::string TextInput::getString(void) {
    return text.getString();
}
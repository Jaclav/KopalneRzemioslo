#include "Button.hpp"

Button::Button(float x, float y, float width, float height, const std::string string) {
    create(x, y, width, height, string);
}

void Button::create(float x, float y, float width, float height, const std::string string) {
    //button
    button.setSize(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(sf::Color(90, 90, 90));

    //outline
    shadow.setSize(sf::Vector2f(width + 10, height + 10));
    shadow.setPosition(x - 5, y - 5);
    shadow.setFillColor(sf::Color::Black);

    //text
    text.setFont(font);
    text.setString(string);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(height / 3);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition((button.getLocalBounds().width - text.getLocalBounds().width) / 2 + button.getPosition().x,
                     (button.getLocalBounds().height - text.getLocalBounds().height * 1.5) / 2 + button.getPosition().y);

    //sound
    if(!soundB.loadFromMemory(button_ogg, button_ogg_len))
        exit(-1);
    sound.setBuffer(soundB);
}

void Button::setStrig(std::string string) {
    text.setString(string);
    text.setPosition((button.getLocalBounds().width - text.getLocalBounds().width) / 2 + button.getPosition().x,
                     (button.getLocalBounds().height - text.getLocalBounds().height * 1.5) / 2 + button.getPosition().y);
    return;
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shadow);
    window.draw(button);
    window.draw(text);
    return;
}

bool Button::isCovering(void) {
    if(isMouseCoveringShape(button)) {
        button.setFillColor(sf::Color(0, 0, 255, 122));
        shadow.setFillColor(sf::Color(0, 0, 255, 122));

        if(playsound && soundOption) {
            sound.play();
            playsound = false;
        }
        return true;
    }
    button.setFillColor(sf::Color(90, 90, 90));
    shadow.setFillColor(sf::Color::Black);

    playsound = true;
    return false;
}

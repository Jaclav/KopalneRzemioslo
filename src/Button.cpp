#include "Button.hpp"

Button::Button(float x, float y, float width, float height, const std::string string) {
    create(x, y, width, height, string);
}

void Button::create(float x, float y, float width, float height, const std::string string) {
    //button
    button.setSize(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(sf::Color(90, 90, 90));
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(5);

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

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
    return;
}

bool Button::isCovering(void) {
    if(isMouseCoveringShape(button)) {
        button.setFillColor(sf::Color(0, 0, 255, 122));

        if(canPlaySound && soundOption) {//play once only when mouse entered
            sound.play();
            canPlaySound = false;
        }
        return true;
    }
    button.setFillColor(sf::Color(90, 90, 90));

    canPlaySound = true;
    return false;
}

void Button::setStrig(std::string string) {
    text.setString(string);
    text.setPosition((button.getLocalBounds().width - text.getLocalBounds().width) / 2 + button.getPosition().x,
                     (button.getLocalBounds().height - text.getLocalBounds().height * 1.5) / 2 + button.getPosition().y);
    return;
}

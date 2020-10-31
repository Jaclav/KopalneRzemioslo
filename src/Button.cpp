#include "Button.hpp"

Button::Button(float x, float y, float width, float height, const sf::String string) {
	create(x, y, width, height, string);
}

void Button::create(float x, float y, float width, float height, const sf::String string) {
    if(!shader.loadFromMemory(shaderStr, sf::Shader::Type::Fragment))
        exit(-1);

    //button
    button.setSize(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(sf::Color(90, 90, 90));

    //text
    text.setFont(font);
    text.setString(string);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(height / 3);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition((button.getLocalBounds().width - text.getLocalBounds().width) / 2 + button.getPosition().x,
                     (button.getLocalBounds().height - text.getLocalBounds().height * 1.5) / 2 + button.getPosition().y);

    //outline
    shadow.setSize(sf::Vector2f(width + 10, height + 10));
    shadow.setPosition(x - 5, y - 5);
    shadow.setFillColor(sf::Color::Black);

    //sound
    if(!soundB.loadFromMemory(button_ogg, button_ogg_len))
        exit(-1);
    sound.setBuffer(soundB);
}

void Button::setStrig(sf::String string) {
    text.setString(string);
    return;
}

void Button::draw(sf::RenderWindow& window) {
    if(displayShader) {
        window.draw(shadow, &shader);
        window.draw(button, &shader);
    }
    else {
        window.draw(shadow);
        window.draw(button);
    }
    window.draw(text);
    return;
}

bool Button::isCovering(void) {
    if(isMouseCoveringShape(button)) {
        displayShader = true;
        if(playsound && soundOption) {
            sound.play();
            playsound = false;
        }
        return true;
    }
    displayShader = false;
    playsound = true;
    return false;
}

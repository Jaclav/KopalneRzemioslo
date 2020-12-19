#include "Crafting.hpp"

Crafting::Crafting(sf::RenderWindow &window) {
    background.setSize(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 3));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(5);
    background.setFillColor(sf::Color(128, 128, 128));
}

Crafting::~Crafting() {
    //dtr
}

void Crafting::draw(sf::RenderWindow &window) {
    if(!isShowing)
        return;

    background.setPosition(window.getView().getCenter().x - background.getLocalBounds().width / 2,
                           window.getView().getCenter().y - background.getLocalBounds().height / 2);
    window.draw(background);
}

bool Crafting::getShowing(void) {
    return isShowing;
}

void Crafting::setShowing(bool onWhat) {
    isShowing = onWhat;
}
#include "Crafting.hpp"

Crafting::Crafting(sf::RenderWindow &window) {
    background.setSize(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 3));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(5);
    background.setFillColor(sf::Color(128, 128, 128, 200));
}

Crafting::~Crafting() {
    //dtr
}

void Crafting::draw(sf::RenderWindow &window, Player &player) {
    if(!isShowing)
        return;

    background.setPosition(window.getView().getCenter().x - background.getLocalBounds().width / 2,
                           window.getView().getCenter().y - background.getLocalBounds().height / 2);
    window.draw(background);

    player.inventory.bar.setPosition(window.getView().getCenter().x - player.inventory.bar.getLocalBounds().width / 2,
                                     window.getView().getCenter().y);
    window.draw(player.inventory.bar);
    for(uint i = 0; i < 10; i++) {
        player.inventory.items->draw(window, window.getView().getCenter().x - player.inventory.bar.getLocalBounds().width / 2 + i * 32 + 3,
                                     window.getView().getCenter().y, player.inventory.typeOfItems[i]);
        player.inventory.number.setPosition(window.getView().getCenter().x - player.inventory.bar.getLocalBounds().width / 2 + i * 32 + 3,
                                            window.getView().getCenter().y);
        player.inventory.number.setString(std::to_string(player.inventory.numberOfItems[i]));
        window.draw(player.inventory.number);
    }
}

bool Crafting::getShowing(void) {
    return isShowing;
}

void Crafting::setShowing(bool onWhat) {
    isShowing = onWhat;
}
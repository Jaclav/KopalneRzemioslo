#include "Player.hpp"

Player::Player(World &world) {
    Player::world = &world;
    playerT.loadFromMemory(playerX_png, playerX_png_len);
    player.setTexture(playerT);
}

Player::~Player() {
    //dtor
}

sf::Vector2f Player::getPosition(void) {
    sf::Vector2f v2f(posX * 64, posY * 64);
    return v2f;
}

void Player::setPosition(uint x, uint y) {//you haven't to check >=0 because var is unsigned
    if(x < world->getSize().x && y < world->getSize().y) {
        posX = x;
        posY = y;
    }
}

uint Player::getV(void) {
    return v;
}

Player::Side Player::getSide(void) {
    return side;
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(player);
    inventory.draw(window);
}

void Player::move(Side side) {
    switch(side) {
        case Up: {
            if(world->getNoclip() || (!isFalling && !isCollision(world->operator()(posX, posY - 1)))) {
                clck.restart();
                posY -= v;
                isFalling = true;
            }
            return;
        }
        case Down: {
            if(world->getNoclip() || (!isCollision(world->operator()(posX, posY + 2))))
                posY += v;
            return;
        }
        case Left: {
            Player::side = Left;
            player.setScale(-1, 1);
            player.setOrigin(player.getLocalBounds().width, 0);
            if(world->getNoclip() || !(isCollision(world->operator()(posX - 1, posY)) || isCollision(world->operator()(posX - 1, posY + 1))))
                posX -= v;
            return;
        }
        case Right: {
            Player::side = Right;
            player.setScale(1, 1);
            player.setOrigin(0, 0);
            if(world->getNoclip() || !(isCollision(world->operator()(posX + 1, posY)) || isCollision(world->operator()(posX + 1, posY + 1))))
                posX += v;
            return;
        }
    }
    return;
}

void Player::update() {
    if(!world->getNoclip()) {
        if(world->operator()(posX, posY + 1) == Items::Ledder) {
            isFalling = false;
        }
        else if(world->operator()(posX, posY + 2) == Items::Leaves) {
            if(clck.getElapsedTime().asMilliseconds() > 700) {
                posY += v;
                clck.restart();
            }
        }
        else if(!isCollision(world->operator()(posX, posY + 2)) && clck.getElapsedTime().asMilliseconds() > 200) {
            if(clck.getElapsedTime().asMilliseconds() % 2 == 0)
                posY += v;
        }
        else if(isCollision(world->operator()(posX, posY + 2))) {
            isFalling = false;
        }
    }
    player.setPosition(posX * 64, posY * 64);
}

void Player::load(const std::string name) {
    inventory.load(name);

    iniFile.setName("saves/" + name + "/world.ini");
    posX = iniFile.readInt("playerPosition", "X", 1000);
    posY = iniFile.readInt("playerPosition", "Y", 62);
}

void Player::save(const std::string name) {
    inventory.save(name);

    iniFile.setName("saves/" + name + "/world.ini");
    iniFile.writeInt("playerPosition", "X", posX);
    iniFile.writeInt("playerPosition", "Y", posY);
}

bool Player::isCollision(uchar item) {
    if(item == Items::Air || item == Items::Grass || item == Items::Leaves || item == Items::Ledder)
        return false;
    return true;
}

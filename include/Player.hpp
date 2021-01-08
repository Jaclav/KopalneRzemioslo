#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System/Vector2.hpp>

#include "Ini.hpp"
#include "Inventory.hpp"
#include "resources.hpp"
#include "tools.hpp"
#include "World.hpp"

class Player {
public:
    Player(World &world);
    ~Player();

    enum Side {Up = 0, Down, Left, Right};

    //getters and setters
    sf::Vector2f getPosition(void);// get position as pixels
    void setPosition(uint x, uint y);// set position as pixels

    uint getV(void);
    Side getSide(void);

    //other
    Inventory inventory;

    void draw(sf::RenderWindow &window);

    //physics
    bool collision();
    void move(Side);
    void update();

    //file operations
    void load(const std::string name);
    void save(const std::string name);

private:
    uint posX = 0, posY = 0;
    uint v = 1;

    Side side;

    bool isFalling = false;
    bool isCollision(uchar item);

    World *world;
    sf::Clock clck;

    sf::Texture playerT;
    sf::Sprite player;

    Ini iniFile;
};

#endif // PLAYER_HPP

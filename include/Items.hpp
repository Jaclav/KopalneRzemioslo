#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <SFML/Graphics.hpp>
#include "Console.hpp"

#include "Animation.hpp"
#include "resources.hpp"
#include "tools.hpp"

class Items {
public:
    Items(float);
    ~Items();

    enum Item {Air = 0, NewLine = '\n', Bedrock = '*', Dirt = '$', Grass = '^', GrassDirt = '#', Leaves = '%', Ledder = '(', Plank = '&', Stone = '@', Wood = '!'};

    void draw(sf::RenderWindow &window, float, float, Item);

private:
    bool wasNotification = false;

    Console console;

    sf::Texture bedrockT;
    sf::Sprite bedrock;

    sf::Texture dirtT;
    sf::Sprite dirt;

    sf::Texture grassT;
    sf::Sprite grass;

    sf::Texture grassDirtT;
    sf::Sprite grassDirt;

    Animation* leaves;

    sf::Texture ledderT;
    sf::Sprite ledder;

    sf::Texture plankT;
    sf::Sprite plank;

    sf::Texture stoneT;
    sf::Sprite stone;

    sf::Texture woodT;
    sf::Sprite wood;

    sf::Texture notFoundT;
    sf::Sprite notFound;
};

#endif // ITEMS_HPP

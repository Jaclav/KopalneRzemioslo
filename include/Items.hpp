#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Console.hpp"
#include "resources.hpp"
#include "tools.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static bool wasNotification = false;//idk why compiler thinks that variable is unuesed, I disable this warning for this line
#pragma GCC diagnostic pop

class Items {
public:
    Items(float);
    ~Items();

    enum Item {Air = 0, NewLine = '\n', Bedrock = '*', CraftingTable = '+', Dirt = '$', Grass = '^', GrassDirt = '#', Leaves = '%', Ledder = '(', Plank = '&', Stone = '@', Wood = '!'};

    void draw(sf::RenderWindow &window, float, float, Item);

private:
    Console console;

    sf::Texture bedrockT;
    sf::Sprite bedrock;

    sf::Texture craftingTableT;
    sf::Sprite craftingTable;

    sf::Texture dirtT;
    sf::Sprite dirt;

    sf::Texture grassT;
    sf::Sprite grass;

    sf::Texture grassDirtT;
    sf::Sprite grassDirt;

    Animation leaves;

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

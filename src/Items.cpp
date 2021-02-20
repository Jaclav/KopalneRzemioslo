#include "Items.hpp"

Items::Items(float factory) : leaves(250) {
    if(!bedrockT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(0, 0, 64, 64)))
        exit(-1);
    bedrock.setTexture(bedrockT);
    bedrock.setScale(factory, factory);

    if(!craftingTableT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(64, 0, 64, 64)))
        exit(-1);
    craftingTable.setTexture(craftingTableT);
    craftingTable.setScale(factory, factory);

    if(!dirtT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(128, 0, 64, 64)))
        exit(-1);
    dirt.setTexture(dirtT);
    dirt.setScale(factory, factory);

    if(!grassT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(192, 0, 64, 64)))
        exit(-1);
    grass.setTexture(grassT);
    grass.setScale(factory, factory);

    if(!grassDirtT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(256, 0, 64, 64)))
        exit(-1);
    grassDirt.setTexture(grassDirtT);
    grassDirt.setScale(factory, factory);

    sf::Texture leavesT;
    if(!leavesT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(128, 64, 64, 64)))
        exit(-1);
    leaves.add(leavesT);
    if(!leavesT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(192, 64, 64, 64)))
        exit(-1);
    leaves.add(leavesT);
    leaves.sprite.setScale(factory, factory);

    if(!ledderT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(320, 0, 64, 64)))
        exit(-1);
    ledder.setTexture(ledderT);
    ledder.setScale(factory, factory);

    if(!notFoundT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(384, 0, 64, 64)))
        exit(-1);
    notFound.setTexture(notFoundT);
    notFound.setScale(factory, factory);

    if(!plankT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(448, 0, 64, 64)))
        exit(-1);
    plank.setTexture(plankT);
    plank.setScale(factory, factory);

    if(!stoneT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(0, 64, 64, 64)))
        exit(-1);
    stone.setTexture(stoneT);
    stone.setScale(factory, factory);

    if(!woodT.loadFromMemory(textures_png, textures_png_len, sf::IntRect(64, 64, 64, 64)))
        exit(-1);
    wood.setTexture(woodT);
    wood.setScale(factory, factory);
}

Items::~Items() {
    //dtor
}

void Items::draw(sf::RenderWindow &window, float x, float y, Item item) {
    switch(item) {
    case Air: {
        break;
    }
    case Bedrock: {
        bedrock.setPosition(x, y);
        window.draw(bedrock);
        break;
    }
    case CraftingTable: {
        craftingTable.setPosition(x, y);
        window.draw(craftingTable);
        break;
    }
    case Dirt: {
        dirt.setPosition(x, y);
        window.draw(dirt);
        break;
    }
    case Grass: {
        grass.setPosition(x, y);
        window.draw(grass);
        break;
    }
    case GrassDirt: {
        grassDirt.setPosition(x, y);
        window.draw(grassDirt);
        break;
    }
    case Leaves: {
        if(leaves.getStatus() == Animation::Stopped)
            leaves.play();
        leaves.sprite.setPosition(x, y);
        leaves.draw(window);
        break;
    }
    case Ledder: {
        ledder.setPosition(x, y);
        window.draw(ledder);
        break;
    }
    case Plank: {
        plank.setPosition(x, y);
        window.draw(plank);
        break;
    }
    case Stone: {
        stone.setPosition(x, y);
        window.draw(stone);
        break;
    }
    case Wood: {
        wood.setPosition(x, y);
        window.draw(wood);
        break;
    }
    case NewLine: {
        //It's new line in file, this code just ignore that.
        break;
    }
    default: {
        if(!wasNotification) {
            console.warning("There is drawing unknown texture!");
            wasNotification = true;
        }
        notFound.setPosition(x, y);
        window.draw(notFound);
        break;
    }
    }
}

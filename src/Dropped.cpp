#include "Dropped.hpp"

Dropped::Dropped() {
    items = new Items(0.4);
}

Dropped::~Dropped() {
    //dtor
}

void Dropped::draw(sf::RenderWindow &window) {
    for(uint i = 0; i < posX.size(); i++) {
        items->draw(window, posX[i] + 16, posY[i] + 32, type[i]);
    }
}

void Dropped::drop(uint x, uint y, Items::Item t, uint q) {
    //unite if same type, X and Y
    for(uint i = 0; i < (uint) posX.size(); i++) {
        if(posX[i] == x && posY[i] == y && type[i] == t) {
            quantity[i] += q;
            return;
        }
    }
    posX.push_back(x);
    posY.push_back(y);
    type.push_back(t);
    quantity.push_back(q);
}

Dropped::Plurality Dropped::collect(uint x, uint y) {
    Plurality plr;
    plr.type = Items::Air;
    for(uint i = 0; i < (uint) posX.size(); i++) {
        if(posX[i] == x && posY[i] == y) {
            plr.type = type[i];
            plr.quantity = quantity[i];

            posX.erase(posX.begin() + i);
            posY.erase(posY.begin() + i);
            type.erase(type.begin() + i);
            quantity.erase(quantity.begin() + i);
            break;
        }
    }
    return plr;
}

void Dropped::load(const std::string name) {
    iniFile.setName("saves/" + name + "/world.ini");

    uint size = iniFile.readInt("dropped", "total", 0);
    if(size == 0)
        return;

    for(uint i = 0; i < size; i++) {
        posX.push_back(iniFile.readInt("dropped", "X" + std::to_string(i), 0));
        posY.push_back(iniFile.readInt("dropped", "Y" + std::to_string(i), 0));
        type.push_back((Items::Item)iniFile.readInt("dropped", "T" + std::to_string(i), Items::Air));
        quantity.push_back(iniFile.readInt("dropped", "Q" + std::to_string(i), 0));
    }
}

void Dropped::save(const std::string name) {
    iniFile.setName("saves/" + name + "/world.ini");

    for(uint i = 0; i < (uint) posX.size(); i++) {
        iniFile.writeInt("dropped", "X" + std::to_string(i), posX[i]);
        iniFile.writeInt("dropped", "Y" + std::to_string(i), posY[i]);
        iniFile.writeInt("dropped", "T" + std::to_string(i), type[i]);
        iniFile.writeInt("dropped", "Q" + std::to_string(i), quantity[i]);
    }
    iniFile.writeInt("dropped", "total", posX.size());
}
#include "Dropped.hpp"

Dropped::Dropped(){
    items = new Items(0.4);
}

Dropped::~Dropped(){
    //dtor
}

void Dropped::draw(sf::RenderWindow &window){
    //if there is no elements in vector, it throw exception
    uint size;
    try{
        size = posX.size();
    }
    catch(...){
        size = 0;
    }

    for(uint i = 0; i < posX.size(); i++){
        items->draw(window, posX[i], posY[i], type[i]);
    }
}

void Dropped::drop(uint x, uint y, Items::Item t, uint q){
    posX.push_back(x);
    posY.push_back(y);
    type.push_back(t);
    quantity.push_back(q);
}

Dropped::Plurality Dropped::collect(uint x, uint y){
    Plurality plr;
	for(uint i = 0; i < (uint) posX.size(); i++) {
		if(posX[i] == x && posX[i] == y) {
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

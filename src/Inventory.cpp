#include "Inventory.hpp"

Inventory::Inventory() {
	items = new Items(0.40);

	number.setFont(font);
	number.setCharacterSize(10);

	barT.loadFromMemory(inventoryBar_png, inventoryBar_png_len);
	bar.setTexture(barT);

	currentItemT.loadFromMemory(currentItem_png, currentItem_png_len);
	currentItem.setTexture(currentItemT);
}

Inventory::~Inventory() {
	//dtor
}

Items::Item Inventory::getTypeOfCurrentItem(void) {
	return typeOfItems[ptr];
}

void Inventory::setPtr(uchar where) {
	if(where < 10)
		ptr = where;
}

void Inventory::incPtr(void) {
	if(ptr == 9)
		ptr = 0;
	else
		ptr++;
}

void Inventory::decPtr(void) {
	if(ptr == 0)
		ptr = 9;
	else
		ptr--;
}

void Inventory::add(Items::Item item) {
	if(typeOfItems[ptr] == Items::Air) {
		typeOfItems[ptr] = item;
		numberOfItems[ptr]++;
	}
	else if(typeOfItems[ptr] == item) {
		numberOfItems[ptr]++;
	}
	else if(ptr < 10) {
		ptr++;
		add(item);
	}
	else {
		//cannot add item TODO: thow something
	}
}

Items::Item Inventory::remove() {
	if(numberOfItems[ptr] > 1) {
		numberOfItems[ptr]--;
	}
	else {
		Items::Item tmp;
		tmp = typeOfItems[ptr];

		typeOfItems[ptr] = Items::Air;
		numberOfItems[ptr] = 0;
		return tmp;
	}
	return typeOfItems[ptr];
}

void Inventory::draw(sf::RenderWindow &window) {
	bar.setPosition(window.getSize().x / 2 + window.getView().getCenter().x - bar.getLocalBounds().width,
	                window.getView().getCenter().y - window.getSize().y / 2);
	window.draw(bar);
	currentItem.setPosition(window.getSize().x / 2 + window.getView().getCenter().x - bar.getLocalBounds().width + ptr * 32,
	                        window.getView().getCenter().y - window.getSize().y / 2);
	window.draw(currentItem);
	for(uint i = 0; i < 10; i++) {
		items->draw(window, window.getSize().x / 2 + window.getView().getCenter().x - bar.getLocalBounds().width + i * 32 + 3,
		            window.getView().getCenter().y - window.getSize().y / 2 + 3, typeOfItems[i]);
		number.setPosition(window.getSize().x / 2 + window.getView().getCenter().x - bar.getLocalBounds().width + i * 32 + 3,
		                   window.getView().getCenter().y - window.getSize().y / 2 + 3);
		number.setString(std::to_string(numberOfItems[i]));
		window.draw(number);
	}
}

#include "Inventory.hpp"

Inventory::Inventory() {
	barT.loadFromMemory(inventoryBar_png, inventoryBar_png_len);
	bar.setTexture(barT);

	currentItemT.loadFromMemory(currentItem_png, currentItem_png_len);
	currentItem.setTexture(currentItemT);
}

Inventory::~Inventory() {
	//dtor
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

void Inventory::add(uchar item) {

}

uchar Inventory::remove() {

}

void Inventory::draw(sf::RenderWindow &window) {
	bar.setPosition(window.getSize().x / 2 + window.getView().getCenter().x - bar.getLocalBounds().width,
	                window.getView().getCenter().y - window.getSize().y / 2);
	window.draw(bar);
	currentItem.setPosition(window.getSize().x / 2 + window.getView().getCenter().x - bar.getLocalBounds().width + ptr * 32,
	                        window.getView().getCenter().y - window.getSize().y / 2);
	window.draw(currentItem);
}

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <SFML/Graphics.hpp>

#include "Items.hpp"
#include "resources.hpp"

class Inventory {
public:
	Inventory();
	~Inventory();

	void setPtr(uchar where);
	void incPtr(void);
	void decPtr(void);

	void add(Items::Item);
	Items::Item remove();

	void draw(sf::RenderWindow &window);

private:
	Items::Item typeOfItems[10] = {Items::Air, Items::Air, Items::Air, Items::Air, Items::Air, Items::Air, Items::Air, Items::Air, Items::Air, Items::Air};
	uchar numberOfItems[10];
	uchar ptr = 0;

	Items* items;

	sf::Texture barT;
	sf::Sprite bar;

	sf::Texture currentItemT;
	sf::Sprite currentItem;
};

#endif // INVENTORY_HPP

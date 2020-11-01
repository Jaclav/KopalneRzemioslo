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

	void add(uchar item);
	uchar remove();

	void draw(sf::RenderWindow &window);

private:
	uchar items[10];
	uchar numberOfItems[10];
	uchar ptr = 0;

	sf::Texture barT;
	sf::Sprite bar;

	sf::Texture currentItemT;
	sf::Sprite currentItem;
};

#endif // INVENTORY_HPP

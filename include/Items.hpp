#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <SFML/Graphics.hpp>
#include "Console.hpp"

#include "resources.hpp"
#include "tools.hpp"

class Items {
public:
	Items(sf::RenderWindow &, float);
	~Items();

	enum Item {Air = 0, NewLine = '\n', Bedrock = '*', Dirt = '$', Grass = '^', GrassDirt = '#', Leaves = '%', Plank = '&', Stone = '@', Wood = '!'};

	void draw(float, float, Item);

private:
	bool wasNotification = false;

	sf::RenderWindow *window;

	Console console;

	sf::Texture bedrockT;
	sf::Sprite bedrock;

	sf::Texture dirtT;
	sf::Sprite dirt;

	sf::Texture grassT;
	sf::Sprite grass;

	sf::Texture grassDirtT;
	sf::Sprite grassDirt;

	sf::Texture leavesT;
	sf::Sprite leaves;

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

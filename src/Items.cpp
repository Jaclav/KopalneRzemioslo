#include "Items.hpp"

Items::Items(float factory) {
	if(!bedrockT.loadFromMemory(bedrock_png, bedrock_png_len))
		exit(-1);
	bedrock.setTexture(bedrockT);
	bedrock.setScale(factory, factory);

	if(!dirtT.loadFromMemory(dirt_png, dirt_png_len))
		exit(-1);
	dirt.setTexture(dirtT);
	dirt.setScale(factory, factory);

	if(!grassDirtT.loadFromMemory(grassDirt_png, grassDirt_png_len))
		exit(-1);
	grassDirt.setTexture(grassDirtT);
	grassDirt.setScale(factory, factory);

	if(!grassT.loadFromMemory(grass_png, grass_png_len))
		exit(-1);
	grass.setTexture(grassT);
	grass.setScale(factory, factory);

	leaves = new Animation(250);

	sf::Texture leavesT;
	if(!leavesT.loadFromMemory(leaves_png, leaves_png_len))
		exit(-1);
	leaves->add(leavesT);
	if(!leavesT.loadFromMemory(leaves2_png, leaves2_png_len))
		exit(-1);
	leaves->add(leavesT);
	leaves->sprite.setScale(factory, factory);

	if(!ledderT.loadFromMemory(ledder_png, ledder_png_len))
		exit(-1);
	ledder.setTexture(ledderT);
	ledder.setScale(factory, factory);


	if(!notFoundT.loadFromMemory(notFound_png, notFound_png_len))
		exit(-1);
	notFound.setTexture(notFoundT);
	notFound.setScale(factory, factory);

	if(!plankT.loadFromMemory(plank_png, plank_png_len))
		exit(-1);
	plank.setTexture(plankT);
	plank.setScale(factory, factory);

	if(!stoneT.loadFromMemory(stone_png, stone_png_len))
		exit(-1);
	stone.setTexture(stoneT);
	stone.setScale(factory, factory);

	if(!woodT.loadFromMemory(wood_png, wood_png_len))
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
			if(leaves->getStatus() == Animation::Stopped)
				leaves->play();
			leaves->sprite.setPosition(x, y);
			leaves->draw(window);
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

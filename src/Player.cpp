#include "Player.hpp"

Player::Player(World &world) {
	Player::world = &world;
	playerT.loadFromMemory(playerX_png, playerX_png_len);
	player.setTexture(playerT);
}

Player::~Player() {
	//dtor
}

sf::Vector2f Player::getPosition(void) {
	sf::Vector2f v2f(posX * 64, posY * 64);
	return v2f;
}

uint Player::getV(void) {
	return v;
}

void Player::draw(sf::RenderWindow &window) {
	window.draw(player);
}

void Player::move(Side side) {
	switch(side) {
		case Up: {
			if(world->getNoclip() || (!isFalling && !isCollision(world->operator()(posX, posY - 1)))) {
				clck.restart();
				posY -= v;
				isFalling = true;
			}
			return;
		}
		case Down: {
			if(world->getNoclip() || (!isCollision(world->operator()(posX, posY + 1))))
				posY += v;
			return;
		}
		case Left: {
			if(world->getNoclip() || (!isCollision(world->operator()(posX - 1, posY))))
				posX -= v;
			return;
		}
		case Right: {
			if(world->getNoclip() || (!isCollision(world->operator()(posX + 1, posY))))
				posX += v;
			return;
		}
	}
	return;
}

void Player::update() {
	if(!world->getNoclip()) {
		if(world->operator()(posX, posY + 1) == Items::Leaves) {
			if(clck.getElapsedTime().asMilliseconds() > 700)
				posY += v;
		}
		else if(!isCollision(world->operator()(posX, posY + 1))  && clck.getElapsedTime().asMilliseconds() > 200) {
			posY += v;
		}
		else if(isCollision(world->operator()(posX, posY + 1))){
			isFalling = false;
		}
	}
	player.setPosition(posX * 64, posY * 64);
}

void Player::load(const std::string name) {
	/*for(unsigned int x = 0; x < 10; x++) {
	    player.inventory[x] = GetPrivateProfileInt("inventory", std::to_string(x).c_str(), 0, name.c_str());
	    player.inventoryNumber[x] = GetPrivateProfileInt("inventoryNumber", std::to_string(x).c_str(), 0, name.c_str());
	}*/

	iniFile.setName("saves/" + name + "/world.ini");
	posX = iniFile.readInt("playerPosition", "X", 0);
	posY = iniFile.readInt("playerPosition", "Y", 62);
}

void Player::save(const std::string name) {
	/*for(unsigned int x = 0; x < 10; x++) {
	    WritePrivateProfileString("inventory", std::to_string(x).c_str(),
	                              std::to_string(player.inventory[x]).c_str(), name.c_str());
	    WritePrivateProfileString("inventoryNumber", std::to_string(x).c_str(),
	                              std::to_string(player.inventoryNumber[x]).c_str(), name.c_str());
	}*/
	iniFile.setName("saves/" + name + "/world.ini");
	iniFile.writeInt("playerPosition", "X", posX);
	iniFile.writeInt("playerPosition", "Y", posY);
}

bool Player::isCollision(uchar item) {
	if(item == Items::Air || item == Items::Grass || item == Items::Leaves)
		return false;
	return true;
}

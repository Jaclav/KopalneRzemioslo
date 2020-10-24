#include "Player.hpp"

Player::Player(uint x, uint y) {
	posX = x;
	posY = y;
}

Player::~Player() {
	//dtor
}

sf::Vector2f Player::getPosition(void) {
	sf::Vector2f v2f(posX, posY);
	return v2f;
}

sf::Vector2f Player::getPosition64(void) {
	sf::Vector2f v2f(posX / 64, posY / 64);
	return v2f;
}

uint Player::getV(void) {
	return v;
}

void Player::update() {

}

void Player::move(Side side) {
	switch(side) {
		case Up: {
			posY -= v;
			break;
		}
		case Down: {
			posY += v;
			break;
		}
		case Left: {
			posX -= v;
			break;
		}
		case Right: {
			posX += v;
			break;
		}
	}
}

void Player::load(const std::string name) {
	/*for(unsigned int x = 0; x < 10; x++) {
	    player.inventory[x] = GetPrivateProfileInt("inventory", std::to_string(x).c_str(), 0, name.c_str());
	    player.inventoryNumber[x] = GetPrivateProfileInt("inventoryNumber", std::to_string(x).c_str(), 0, name.c_str());
	}*/

	iniFile.setName("saves/" + name + "/world.ini");
	posX = iniFile.readInt("playerPosition", "X", 0);
	posY = iniFile.readInt("playerPosition", "Y", 0);
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

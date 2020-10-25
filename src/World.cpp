#include "World.hpp"

World::World() {
	reset();
#ifdef _WIN32
	mkdir("saves");
#else
	system("mkdir saves 2> /dev/null");
#endif
}

World::~World() {
	file.close();
	reset();
}

uchar& World::operator () (uint r, uint c) {
	if(r < sizeX && c < sizeY) {
		return map[r][c];
	}
	else {
		console.error(std::to_string(r) + " X " + std::to_string(c) + " is outside the array!");
		exit(-1);//Without this is warning, it won't be executed
	}
}

sf::Vector2u World::getSize(void) {
	sf::Vector2u v2u(sizeX, sizeY);
	return v2u;
}

sf::Vector2u World::getSize64(void) {
	sf::Vector2u v2u(sizeX / 64, sizeY / 64);
	return v2u;
}

std::string World::getName(void) {
	return name;
}

void World::setName(std::string newName) {
#ifdef _WIN32
	rmdir(std::string("saves/" + name).c_str());
#else
	system(std::string(std::string("mkdir ") + std::string("saves/" + name)).c_str());
#endif // _WIN32
	name = newName;
	save();
}

void World::generate(void) {//TODO: do it better
	console.log("Generating terrain.");

	uint y = 64, lastTreePosX = 0, treeIt;
	bool tmp = false;

	reset();

	if(seed == 0) {
		srand(time(NULL) + rand());
	}
	else {
		srand(seed);
	}

	for(uint x = 0; x < sizeX; x++) {
		//generating line of terrain
		if(rand() % 13 == 1) { // 1/13 change side
			if(rand() % 2 == 1)
				tmp = true;
			else
				tmp = false;
		}
		if(rand() % 3 == 1) { // 2/3 is flat
			if(tmp) {//go down
				if(y >= sizeY - 1)
					tmp = false;
				else
					y++;
			}
			else {//go up
				if(y <= 2)
					tmp = true;
				else
					y--;
			}
		}

		//stone and bedrock level
		for(uint k = y; k < sizeY; k++) {
			map[x][k] = Items::Stone;
		}

		map[x][sizeY - 1] = Items::Bedrock;

		//dirt level
		map[x][y] = Items::GrassDirt;
		map[x][y + 1] = Items::Dirt;
		map[x][y + 2] = Items::Dirt;
		map[x][y + 3] = Items::Dirt;

		//trees
		if(x >  5 && y > 14 && x + 5 < sizeX && lastTreePosX + 6 < x && rand() % 3 == 1) {
			for(treeIt = 1; treeIt <= (uint) rand() % 7 + 7; treeIt++) {
				map[x][y - treeIt] = Items::Wood;

				if(treeIt > 3) {
					map[x - 1][y - treeIt] = Items::Leaves;
					map[x + 1][y - treeIt] = Items::Leaves;
				}
			}
			map[x][y - treeIt] = Items::Leaves;
			lastTreePosX = x;
		}

		//grass
		if(rand() % 4 == 1 && map[x][y - 1] == 0)
			map[x][y - 1] = Items::Grass;
	}

	console.log("Terrain generated.");
	return;
}

void World::save(void) {
	//saving world
#ifdef _WIN32
	mkdir(name.c_str());
#else
	system(std::string("mkdir saves/" + name + " 2> /dev/null").c_str());
#endif // _WIN32

	file.close();
	file.open("saves/" + name + "/world.sav", std::ios::out | std::ios::binary);
	if(!file.good()) {
		console.warning("Problem with saving world file, file has not been saved.");
		return;
	}
	for(unsigned int y = 0; y < sizeY; y++) {
		for(unsigned int x = 0; x < sizeX; x++) {
			file << map[x][y];
		}
		file << '\n';
	}
	file.close();

	//saving other info
	iniFile.setName("saves/" + name + "/world.ini");

	iniFile.writeString("worldInfo", "version", version);
	iniFile.writeInt("worldInfo", "seed", seed);
	iniFile.writeInt("worldInfo", "allowCommands", allowCommands);
	iniFile.writeInt("worldInfo", "noclip", noclip);

	console.log("World files saved.");
	return;
}

void World::load(void) {
	reset();

	//loading world
	file.close();
	file.open("saves/" + name + "/world.sav", std::ios::in | std::ios::binary);
	if(!file.good()) {
		console.warning("Problem with loading world file.");
		return;
	}
	std::string line = "";
	uint y = 0;

	while(std::getline(file, line, '\n')) {
		for(uint x = 0; x < line.length() && x < sizeX; x++) {
			map[x][y] = (Items::Item) line[x];
		}
		y++;
	}
	file.close();

	//loading other info
	iniFile.setName("saves/" + name + "/world.ini");

	if(iniFile.readString("worldInfo", "version", version) != std::string(version)) {
		console.warning("This world was created in a different version than the game! The world was backed up.");
		//Backup
#ifdef _WIN32
		system(std::string("xcopy \"saves/" + name + "\" \"saves/" + name + ".bac\").c_str());
#else
		system(std::string("cp -r saves/" + name + " saves/" + name + ".bac").c_str());
#endif // _WIN32
	}
	seed = iniFile.readInt("worldInfo", "seed", 0);
	allowCommands = iniFile.readInt("worldInfo", "allowCommands", 0);
	noclip = iniFile.readInt("worldInfo", "noclip", 0);

	console.log("World files loaded.");
	return;
}

void World::reset(void) {
	for(uint x = 0; x < sizeX; x++) {
		for(uint y = 0; y < sizeY; y++) {
			map[x][y] = Items::Air;
		}
	}
}

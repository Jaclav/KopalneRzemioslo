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
		exit(0);//Without this is warning, it won't be executed
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

	uint y = 30, lastTreePosX = 0, treeIt;
	bool tmp = false;

	reset();

	if(seed == 0) {
		srand(time(NULL) + rand());
	}
	else {
		srand(seed);
	}

	//generating line of terrain
	for(uint x = 0; x < sizeX; x++) {
		if(rand() % 13 == 1) { // 1/12 change side
			if(rand() % 2 == 1)
				tmp = true;
			else
				tmp = false;
		}
		if(rand() % 3 == 1) { // 1/3 is flat
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

/*void World::generateStructures(uint posX, unsigned  int posY) {//TODO: do it better
	uchar *str, *prop;
	uint structureSizeX = 0, structureSizeY = 0;

	switch(rand() % 3) {
		case 0:
			str = &dick.str[0][0];
			prop = &dick.prop;
			structureSizeX = 7;
			structureSizeY = 8;
			break;
		case 1:
			str = &home.str[0][0];
			prop = &home.prop;
			structureSizeX = 5;
			structureSizeY = 4;
			break;
		case 2:
			str = &pot.str[0][0];
			prop = &pot.prop;
			structureSizeX = 3;
			structureSizeY = 3;
			break;
	}

	posY -= structureSizeY - 1;

	if(posX + structureSizeX < sizeX && lastStructurePosX < posX - structureSizeX - 5 && lastTreePosX < posX - structureSizeX - 3 && rand() % 100 < *prop) {
		for(uint x = 0; x < structureSizeX; x++) {
			for(uint y = 0; y < structureSizeY; y++) {
				map[x + posX][y + posY] = *(str + x * structureSizeY + y);
			}
		}
		lastStructurePosX = posX;
	}
	return;
}*/

void World::save(void) {
	//saving world
	std::string name = "saves/" + World::name;
#ifdef _WIN32
	mkdir(name.c_str());
#else
	system(std::string(std::string("mkdir ") + name).c_str());
#endif // _WIN32

	file.close();
	file.open(name + "/world.sav", std::ios::out | std::ios::binary);
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
	name += "/world.ini";

	/*WritePrivateProfileString("worldInfo", "version", version, name.c_str());
	WritePrivateProfileString("worldInfo", "seed", std::to_string(seed).c_str(), name.c_str());
	WritePrivateProfileString("worldInfo", "allowCommands", std::to_string(allowCommands).c_str(), name.c_str());
	WritePrivateProfileString("worldInfo", "noclip", std::to_string(noclip).c_str(), name.c_str());*/

	console.log("World files saved.");
	return;
}

void World::load(void) {
	std::string name = World::name;
	reset();

	//loading world
	name = "saves/" + name;
	file.close();
	file.open(name + "/world.sav", std::ios::in | std::ios::binary);
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
	name += "/world.ini";
	iniFile.setName(name);

	if(iniFile.readString("worldInfo", "version", version) != std::string(version)) {
		console.warning("This world was created in another version than current version!");
		return;
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

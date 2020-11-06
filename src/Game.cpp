#include "Game.hpp"
#define mouseInWorldX (sf::Mouse::getPosition().x + view.getCenter().x - window->getSize().x / 2 ) / 64
#define mouseInWorldY (sf::Mouse::getPosition().y + view.getCenter().y - window->getSize().y / 2 ) / 64

Game::Game(sf::RenderWindow &_window, World &_world) {
	world = &_world;
	window = &_window;
	items = new Items(1);
	view = window->getView();

	player = new Player(*world);

	diggingB.loadFromMemory(digging_ogg, digging_ogg_len);
	digging.setBuffer(diggingB);

	puttingB.loadFromMemory(putting_ogg, putting_ogg_len);
	putting.setBuffer(puttingB);
	putting.setVolume(20);

	consoleBackground.setSize(sf::Vector2f(500, 200));
	consoleBackground.setFillColor(sf::Color(50, 50, 50, 150));

	consoleText.setFont(font);
	consoleText.setCharacterSize(30);
	consoleText.setString("\n>");
}

Game::~Game() {
	digging.stop();
	putting.stop();

	delete items;
}

Game::Returned Game::play(Menu &menu) {
	uint drawFromX = 0, drawFromY = 0, drawToX = 0, drawToY = 0;

	sf::Text debugText("", font, 50);

	player->load(world->getName());
	view.setCenter(player->getPosition());

	while(window->isOpen()) {
		while(window->pollEvent(event)) {
			if(event.type == event.Closed) {
				window->close();
			}
			//moving player
			if(!showConsole && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if(player->getPosition().y > 0)
					player->move(Player::Up);
				window->pollEvent(event);
				break;
			}
			if(!showConsole && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if(player->getPosition().y / 64 + 2 < world->getSize().y)
					player->move(Player::Down);
				window->pollEvent(event);
				break;
			}
			if(!showConsole && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				if(player->getPosition().x > 0)
					player->move(Player::Left);
				window->pollEvent(event);
				break;
			}
			if(!showConsole && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				if(player->getPosition().x / 64 + 1 < world->getSize().x)
					player->move(Player::Right);
				window->pollEvent(event);
				break;
			}
			//mouse
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //destroy
				if(mouseInWorldX > 0 && mouseInWorldX < world->getSize().x && mouseInWorldY > 0 && mouseInWorldY < world->getSize().y &&
				        world->operator()(mouseInWorldX, mouseInWorldY) != Items::Bedrock && world->operator()(mouseInWorldX, mouseInWorldY) != Items::Air) {
					if(!player->inventory.add(world->operator()(mouseInWorldX, mouseInWorldY))) {
						if(soundOption)
							digging.play();
						world->operator()(mouseInWorldX, mouseInWorldY) = Items::Air;
					}
				}
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) { //put
				if(mouseInWorldX > 0 && mouseInWorldX < world->getSize().x && mouseInWorldY > 0 && mouseInWorldY < world->getSize().y &&
				        world->operator()(mouseInWorldX, mouseInWorldY) == Items::Air && player->inventory.getTypeOfCurrentItem() != Items::Air &&
				        ((uint)mouseInWorldX != player->getPosition().x / 64 || ((uint)mouseInWorldY != player->getPosition().y / 64 && (uint)mouseInWorldY != player->getPosition().y / 64 + 1))) {
					if(soundOption)
						putting.play();
					world->operator()(mouseInWorldX, mouseInWorldY) =  player->inventory.remove();
				}
			}
			//changing inventory pointer by mouse's wheel
			if(event.type == sf::Event::MouseWheelMoved) {
				if(event.mouseWheel.delta > 0) {
					player->inventory.decPtr();

				}
				else if(event.mouseWheel.delta < 0) {
					player->inventory.incPtr();
				}
			}
			//changing inventory pointer by pressing number
            if(!showConsole && event.type == sf::Event::TextEntered && event.text.unicode > 47 && event.text.unicode < 58){
                player->inventory.setPtr(event.text.unicode == 48 ? 9 : event.text.unicode - 49);
            }
            //pop
            if(!showConsole && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
                    while(player->inventory.remove() != Items::Air);
                }
                else{
                    player->inventory.remove();
                }
                window->pollEvent(event);
				break;
            }
			//Fs
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
				showDebug = !showDebug;
				window->pollEvent(event);
				break;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) {
				printScreen(*window);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type  == event.LostFocus) {
				view.setCenter(window->getSize().x / 2, window->getSize().y / 2);
				window->setView(view);
				window->pollEvent(event);

				returned = menu.pause();

				if(returned == Menu::Save) {
					world->save();
					player->save(world->getName());
				}
				else if(returned == Menu::SaveAndExit) {
					world->save();
					player->save(world->getName());
					window->pollEvent(event);
					return Back;
				}
				view.setCenter(player->getPosition());
				window->setView(view);
			}
			//console
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)) {
				showConsole = !showConsole;
				window->pollEvent(event);
				break;
			}
			if(showConsole && event.type == sf::Event::TextEntered && event.text.unicode > 31) {
				command.push_back(event.text.unicode);
				consoleText.setString(commandInfo + "\n>" + command);
			}
			if(showConsole && sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
				if(command.size() > 0)
					command.pop_back();
				consoleText.setString(commandInfo + "\n>" + command);
				window->pollEvent(event);
				break;
			}
			if(showConsole && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				interpreter();
				command = "";
				consoleText.setString(commandInfo + "\n>");
			}
		}

		player->update();

		if(player->getPosition().x > view.getCenter().x + 128 || player->getPosition().x + 128 < view.getCenter().x ||
		        player->getPosition().y > view.getCenter().y + 128 || player->getPosition().y + 128 < view.getCenter().y) {
			if(player->getPosition().x > view.getCenter().x) {
				view.setCenter(view.getCenter().x + 21.333333333, view.getCenter().y);
			}
			if(player->getPosition().x < view.getCenter().x) {
				view.setCenter(view.getCenter().x - 21.333333333, view.getCenter().y);
			}
			if(player->getPosition().y > view.getCenter().y) {
				view.setCenter(view.getCenter().x, view.getCenter().y + 21.333333333);
			}
			if(player->getPosition().y < view.getCenter().y) {
				view.setCenter(view.getCenter().x, view.getCenter().y - 21.333333333);
			}
		}
		window->setView(view);

		drawFromX = (view.getCenter().x > window->getSize().x / 2 ? view.getCenter().x - window->getSize().x / 2 : 1) / 64 - 1;
		drawFromY = (view.getCenter().y > window->getSize().y / 2 ? view.getCenter().y - window->getSize().y / 2 : 1) / 64 - 1;

		drawToX = drawFromX + (window->getSize().x) / 64 + 3;
		drawToY = drawFromY + (window->getSize().y) / 64 + 3;
		if(drawToY >= world->getSize().y) {
			drawToY = world->getSize().y;
		}
		if(drawToX >= world->getSize().x) {
			drawToX = world->getSize().x;
		}

		//drawing
		window->clear();

		for(uint x = drawFromX; x < drawToX; x++) {
			for(uint y = drawFromY; y < drawToY; y++) {
				items->draw(*window, x * 64, y * 64, (Items::Item) world->operator()(x, y));
			}
		}

		if(showDebug) {
			debugText.setString(std::to_string(player->getPosition().x / 64) + " " + std::to_string(player->getPosition().y / 64));
			debugText.setPosition(view.getCenter().x - window->getSize().x / 2, view.getCenter().y - window->getSize().y / 2);
			window->draw(debugText);
		}

		if(showConsole) {
			consoleBackground.setPosition(view.getCenter().x - window->getSize().x / 2,
			                              view.getCenter().y + window->getSize().y / 2 - consoleBackground.getSize().y);
			consoleText.setPosition(view.getCenter().x - window->getSize().x / 2 + 10,
			                        view.getCenter().y + window->getSize().y / 2 - 80);
			window->draw(consoleBackground);
			window->draw(consoleText);
		}
		player->draw(*window);

		window->display();
	}
	world->save();
	player->save(world->getName());
	return Quit;
}

void Game::interpreter() {
    if(!world->allowCommands){
        commandInfo = "Commands aren't allowed!";
        return;
    }

	std::string cmd = command.substr(0, command.find(' '));
	command = command.substr(command.find(' ') + 1, command.size() - command.find(' '));
	std::string p1 = command.substr(0, command.find(' '));
	std::string p2 = command.substr(command.find(' ') + 1, command.size());

	if(cmd == "tp") {
		try {
			player->setPosition(std::stoi(p1), std::stoi(p2));
			view.setCenter(player->getPosition());
		}
		catch(...) {
			commandInfo = "Wrong parameter!";
			return;
		}
		commandInfo = "Teleported";
	}
	else if(cmd == "add") {
		Items::Item item;
		if(p1 == "bedrock")
			item = Items::Bedrock;
		else if(p1 == "dirt")
			item = Items::Dirt;
		else if(p1 == "grass")
			item = Items::Grass;
		else if(p1 == "grassDirt")
			item = Items::GrassDirt;
		else if(p1 == "leaves")
			item = Items::Leaves;
		else if(p1 == "ledder")
			item = Items::Ledder;
		else if(p1 == "plank")
			item = Items::Plank;
		else if(p1 == "stone")
			item = Items::Stone;
		else if(p1 == "wood")
			item = Items::Wood;
		else {
			commandInfo = "Unknown block!";
			return;
		}

		uint howMany;

		std::cout << p2 << "<\n";

		if(p2 == "ledder") {
			howMany = 1;
		}
		else {
			try {
				howMany = std::stoi(p2);
			}
			catch(...) {
				commandInfo = "Wrong parameter!";
				return;
			}
		}

		for (uint i = 0; i < howMany; i++) {
			if(player->inventory.add(item)) {
				break;//when cannot add more
			}
		}

		commandInfo = "Block added";
		return;
	}
    else if(cmd == "noclip"){
        try {
            world->noclip = std::stoi(p1);
        }
        catch(...){
            commandInfo = "Wrong parameter!";
            return;
        }
        commandInfo = "Noclip setted";
    }
    else if(cmd == "allowCommands"){
        try{
            world->allowCommands = std::stoi(p1);
        }
        catch(...){
            commandInfo = "Wrong parameter!";
            return;
        }
        commandInfo = "AllowCommands setted";
    }
	else if(cmd != "") {
		commandInfo = "Unknown command!";
	}
	return;
}


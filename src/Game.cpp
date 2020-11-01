#include "Game.hpp"
#define mouseInWorldX (sf::Mouse::getPosition().x + view.getCenter().x - window->getSize().x / 2 ) / 64
#define mouseInWorldY (sf::Mouse::getPosition().y + view.getCenter().y - window->getSize().y / 2 ) / 64

Game::Game(sf::RenderWindow &_window, World &_world) {
	world = &_world;
	window = &_window;
	items = new Items(*window, 1);
	view = window->getView();

	diggingB.loadFromMemory(digging_ogg, digging_ogg_len);
	digging.setBuffer(diggingB);

	puttingB.loadFromMemory(putting_ogg, putting_ogg_len);
	putting.setBuffer(puttingB);
	putting.setVolume(20);
}

Game::~Game() {
	digging.stop();
	putting.stop();

	delete items;
}

Game::Returned Game::play(Menu &menu) {
	uint drawFromX = 0, drawFromY = 0, drawToX = 0, drawToY = 0;

	sf::Text debugText("", font, 50);

	Player player(*world);
	player.load(world->getName());
	view.setCenter(player.getPosition());

	while(window->isOpen()) {
		while(window->pollEvent(event)) {
			if(event.type == event.Closed) {
				window->close();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if(player.getPosition().y > 0)
					player.move(Player::Up);
				window->pollEvent(event);
				break;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if(player.getPosition().y / 64 + 1< world->getSize().y)
					player.move(Player::Down);
				window->pollEvent(event);
				break;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				if(player.getPosition().x > 0)
					player.move(Player::Left);
				window->pollEvent(event);
				break;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				if(player.getPosition().x / 64 + 1 < world->getSize().x)
					player.move(Player::Right);
				window->pollEvent(event);
				break;
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //destroy
				if(mouseInWorldX > 0 && mouseInWorldX < world->getSize().x && mouseInWorldY > 0 && mouseInWorldY < world->getSize().y &&
				        world->operator()(mouseInWorldX, mouseInWorldY) != Items::Bedrock && world->operator()(mouseInWorldX, mouseInWorldY) != Items::Air) {
					if(soundOption)
						digging.play();
					world->operator()(mouseInWorldX, mouseInWorldY) = Items::Air;
				}
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) { //put
				if(mouseInWorldX > 0 && mouseInWorldX < world->getSize().x && mouseInWorldY > 0 && mouseInWorldY < world->getSize().y &&
				        world->operator()(mouseInWorldX, mouseInWorldY) == Items::Air) {
					if(soundOption)
						putting.play();
					world->operator()(mouseInWorldX, mouseInWorldY) =  Items::Stone;
				}
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
					player.save(world->getName());
				}
				else if(returned == Menu::SaveAndExit) {
					world->save();
					player.save(world->getName());
					return Back;
				}
				view.setCenter(player.getPosition());
				window->setView(view);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
				showDebug = !showDebug;
				break;
			}
		}

		player.update();

		if(player.getPosition().x > view.getCenter().x + 128 || player.getPosition().x + 128 < view.getCenter().x ||
		        player.getPosition().y > view.getCenter().y + 128 || player.getPosition().y + 128 < view.getCenter().y) {
			if(player.getPosition().x > view.getCenter().x) {
				view.setCenter(view.getCenter().x + 32 / 1.5, view.getCenter().y);
			}
			if(player.getPosition().x < view.getCenter().x) {
				view.setCenter(view.getCenter().x - 32 / 1.5, view.getCenter().y);
			}
			if(player.getPosition().y > view.getCenter().y) {
				view.setCenter(view.getCenter().x, view.getCenter().y + 32 / 1.5);
			}
			if(player.getPosition().y < view.getCenter().y) {
				view.setCenter(view.getCenter().x, view.getCenter().y - 2 / 1.5);
			}
		}
		window->setView(view);

		drawFromX = (view.getCenter().x > window->getSize().x / 2 ? view.getCenter().x - window->getSize().x / 2 : 1) / 64 - 1;
		drawFromY = (view.getCenter().y > window->getSize().y / 2 ? view.getCenter().y - window->getSize().y / 2 : 1) / 64 - 1;

		drawToX = drawFromX + (window->getSize().x) / 64 + 2;
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
				items->draw(x * 64, y * 64, (Items::Item) world->operator()(x, y));
			}
		}

		if(showDebug) {
			debugText.setString(std::to_string(player.getPosition().x / 64) + " " + std::to_string(player.getPosition().y / 64));
			debugText.setPosition(view.getCenter().x - window->getSize().x / 2, view.getCenter().y - window->getSize().y / 2);
			window->draw(debugText);
		}
		player.draw(*window);

		window->display();
	}
	world->save();
	player.save(world->getName());
	return Quit;
}

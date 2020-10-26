#include "Game.hpp"

Game::Game(sf::RenderWindow &_window, World &_world) {
	world = &_world;
	window = &_window;
	items = new Items(*window, 1);
	view = window->getView();
}

Game::~Game() {
	delete items;
}

Game::Returned Game::play(Menu &menu) {
	uint drawFromX = 0, drawFromY = 0, drawToX = 0, drawToY = 0;

	sf::Text debugText("", font, 50);

	Player player(64, 64);
	player.load(world->getName());

	while(window->isOpen()) {
		while(window->pollEvent(event)) {
			if(event.type == event.Closed) {
				window->close();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if(player.getPosition64().y > 0)
					player.move(Player::Up);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if(player.getPosition64().y + window->getSize().y / 128 + 1 < world->getSize().y)
					player.move(Player::Down);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				if(player.getPosition64().x > 0)
					player.move(Player::Left);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				if(player.getPosition64().x + window->getSize().x / 128 + 1 < world->getSize().x)
					player.move(Player::Right);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) {
				printScreen(*window);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type  == event.LostFocus) {
				view.setCenter(window->getSize().x / 2, window->getSize().y / 2);
				window->setView(view);

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
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
				showDebug = !showDebug;
				break;
			}
		}

		player.update();

		//TODO: do it better
		if(player.getPosition().x > view.getCenter().x + 128 || player.getPosition().x + 128 < view.getCenter().x ||
		        player.getPosition().y > view.getCenter().y + 128 || player.getPosition().y + 128 < view.getCenter().y) {
			view.setCenter(player.getPosition());
		}
		window->setView(view);

		drawFromX = (view.getCenter().x > window->getSize().x / 2 ? view.getCenter().x - window->getSize().x / 2 : 1) / 64 - 1;
		drawFromY = (view.getCenter().y > window->getSize().y / 2 ? view.getCenter().y - window->getSize().y / 2 : 1) / 64 - 1;

		drawToX = drawFromX + (window->getSize().x) / 64 + 2;
		drawToY = drawFromY + (window->getSize().y) / 64 + 3;

		//drawing
		window->clear();

		for(uint x = drawFromX; x < drawToX; x++) {
			for(uint y = drawFromY; y < drawToY; y++) {
				items->draw(x * 64, y * 64, (Items::Item) world->operator()(x, y));
			}
		}

		if(showDebug) {
			debugText.setString(std::to_string(player.getPosition64().x) + " " + std::to_string(player.getPosition64().y));
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

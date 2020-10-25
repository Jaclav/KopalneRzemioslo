#include "Menu.hpp"

Menu::Menu(sf::RenderWindow &_window) {
	window = &_window;

	if(!themeB.loadFromMemory(menuTheme_ogg, menuTheme_ogg_len))
		exit(-1);
	theme.setBuffer(themeB);
	theme.setVolume(75);
	theme.setLoop(true);

	if(!dirtBackgroundT.loadFromMemory(dirtBackground_png, dirtBackground_png_len))
		exit(-1);
	dirtBackground.setTexture(dirtBackgroundT);
	dirtBackground.setScale(window->getSize().x / dirtBackground.getLocalBounds().width,
	                        window->getSize().y / dirtBackground.getLocalBounds().height);

	if(!startBackgroundT.loadFromMemory(startBackground_png, startBackground_png_len))
		exit(-1);
	startBackground.setTexture(startBackgroundT);
	startBackground.setScale(window->getSize().x / startBackground.getLocalBounds().width,
	                         window->getSize().y / startBackground.getLocalBounds().height);

	mainText.setFont(font);
	mainText.setOutlineThickness(2);
	mainText.setOutlineColor(sf::Color::Black);
}

Menu::~Menu() {
	theme.stop();
}

Menu::Returned Menu::info(void) {
	playTheme();

	//main text
	mainText.setString("Game created by: Jacek 'Dobromir'\nTextures created by: Skryty\nGraphic library: SFML created by Laurent Gomila");
	mainText.setCharacterSize(80);
	mainText.setPosition((window->getSize().x - mainText.getLocalBounds().width) / 2, 100);

	//buttons
	Button backButton(window->getSize().x / 2 - 250, window->getSize().y - 125, 500, 100, "Back");

	while(window->isOpen()) {
		while(window->pollEvent(event)) {
			if(event.type == event.Closed) {
				window->close();
			}
			else if(backButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return Back;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) {
				printScreen(*window);
			}
		}
		window->clear();

		window->draw(dirtBackground);
		window->draw(mainText);
		backButton.draw(*window);

		window->display();
	}
	return Quit;
}

Menu::Returned Menu::options(void) {
	playTheme();

	//main text
	mainText.setString("Options");
	mainText.setCharacterSize(80);
	mainText.setPosition((window->getSize().x - mainText.getLocalBounds().width) / 2, 100);

	//buttons
	Button hardExitButton(window->getSize().x / 2 - 250, window->getSize().y - 125, 500, 100, "Exit without applying");
	Button loudnessButton(100, 200, 500, 100, soundOption ? "Set mute" : "Set loud");
	Button saveExitButton(window->getSize().x / 2 - 250, window->getSize().y - 250, 500, 100, "Apply and back");

	//other info
	sf::Text infoText("AWSD - moving\nRMouse - Put block\nLMouse - Destroy block\nF12 - screenshot\nESC - exit and save the world", font, 50);
	infoText.setPosition(100, 450);

	while(window->isOpen()) {
		while(window->pollEvent(event)) {
			if(event.type == event.Closed) {
				window->close();
			}
			else if(saveExitButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return Save;
			}
			else if(hardExitButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return DontSave;
			}
			else if(loudnessButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				if(soundOption) {
					loudnessButton.setStrig("Set loud");
					soundOption = false;
				}
				else {
					loudnessButton.setStrig("Set mute");
					soundOption = true;
				}
				playTheme();
				break;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) {
				printScreen(*window);
			}
		}
		window->clear();
		window->draw(dirtBackground);
		window->draw(mainText);
		window->draw(infoText);

		hardExitButton.draw(*window);
		loudnessButton.draw(*window);
		saveExitButton.draw(*window);

		window->display();
	}
	return Quit;
}

Menu::Returned Menu::pause(void) {
	sf::Texture backgroundT;
	sf::Sprite background;
	sf::Color backgroundColor;

	backgroundT.create(window->getSize().x, window->getSize().y);
	backgroundT.update(*window);

	background.setTexture(backgroundT);
	backgroundColor = background.getColor();
	backgroundColor.a = 100;
	background.setColor(backgroundColor);

	Button backButton(window->getSize().x / 2 - 250, window->getSize().y / 2, 500, 100, "Back to game");
	Button saveButton(window->getSize().x / 2 - 250, window->getSize().y / 2 + 125, 500, 100, "Save game");
	Button saveAndExitButton(window->getSize().x / 2 - 250, window->getSize().y / 2 + 250, 500, 100, "Save and exit");

	while(window->isOpen()) {
		while(window->pollEvent(event)) {
			if(event.type == event.Closed) {
				window->close();
			}
			else if(backButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return Back;
			}
			else if(saveButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return Save;
			}
			else if(saveAndExitButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return SaveAndExit;
			}
		}
		window->clear();
		window->draw(background);

		backButton.draw(*window);
		saveButton.draw(*window);
		saveAndExitButton.draw(*window);

		window->display();
	}
	return Quit;
}

Menu::Returned Menu::play(World &world) {
	playTheme();

	enum Chosen {TypeName, TypeSeed};
	Chosen chosen = TypeName;

	//main text
	mainText.setString("Worlds");
	mainText.setCharacterSize(80);
	mainText.setPosition((window->getSize().x - mainText.getLocalBounds().width) / 2, 100);

	//worlds list
	sf::Text worlds("", font, 40);
	worlds.setPosition(0, 0);

	struct dirent *entry = nullptr;
	DIR *dp = nullptr;
	dp = opendir("./saves/");
	if(dp != nullptr) {
		while((entry = readdir(dp))) {
			if(entry->d_name[0] != '.')
				worlds.setString(worlds.getString() + entry->d_name + "\n");
		}
	}
	closedir(dp);

	//world name
	std::string name = "";
	sf::Text nameText("", font, 80);
	nameText.setPosition(window->getSize().x / 2 - 350, 400);

	//world seed
	uint seed = 0;
	sf::Text seedText("0", font, 80);
	seedText.setPosition(window->getSize().x / 2 - 350, 600);

	//background for world seed and name
	sf::RectangleShape nameBackground;
	nameBackground.setPosition(nameText.getPosition());
	nameBackground.setSize(sf::Vector2f(700, 100));
	nameBackground.setFillColor(sf::Color(48, 26, 0, 200));

	sf::RectangleShape seedBackground;
	seedBackground.setPosition(seedText.getPosition());
	seedBackground.setSize(sf::Vector2f(700, 100));
	seedBackground.setFillColor(sf::Color(48, 26, 0, 200));

	//buttons
	Button backButton(window->getSize().x / 2 - 250, window->getSize().y - 125, 500, 100, "Back");
	Button commandsOptionButton((window->getSize().x - 500) / 2, window->getSize().y - 375, 500, 100, world.allowCommands ? "Allow Commands" : "Don't Allow Commands");
	Button loadWorldButton(window->getSize().x / 2 + 12.5, window->getSize().y - 250, 237.5, 100, "Load World");
	Button newWorldButton(window->getSize().x / 2 - 250, window->getSize().y - 250, 237.5, 100, "New World");

	//info text
	sf::Text infoText("", font, 60);
	infoText.setPosition(0, 0);
	infoText.setFillColor(sf::Color::Cyan);

	while(window->isOpen()) {
		while(window->pollEvent(event)) {
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && infoText.getString() != "") { //hide info text
				infoText.setString("");
			}

			if(event.type == event.Closed) {
				window->close();
			}
			else if(backButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return Back;
			}
			else if(loadWorldButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { //load world
				std::fstream file("saves/" + name + "/world.sav", std::ios::in | std::ios::binary);
				if(file.good()) {
					file.close();
					world.name = name;
					return LoadWorld;
				}
				else {
					file.close();
					infoText.setString("This save doesn't exists!");
				}
			}
			else if(newWorldButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { //new world
				if(name.size() != 0) {
					std::fstream file("saves/" + name + "/world.sav", std::ios::in | std::ios::binary);
					if(file.good()) {
						infoText.setString("This world already exists!");
						file.close();
					}
					else {
						file.close();

						world.name = name;
						world.seed = seed;
						return NewWorld;
					}
				}
				else {
					infoText.setString("Type world name!");
				}
			}
			else if(commandsOptionButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { //commands option
				if(world.allowCommands) {
					world.allowCommands = false;
					commandsOptionButton.setStrig("Don't Allow Commands");
				}
				else {
					world.allowCommands = true;
					commandsOptionButton.setStrig("Allow Commands");
				}
				break;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) {
				printScreen(*window);
			}
			else if(event.type == sf::Event::TextEntered) { //typing text
				if(chosen == TypeName && nameText.getLocalBounds().width + 40 < nameBackground.getLocalBounds().width &&
				        (event.text.unicode > 47 || event.text.unicode == 32)) { //type name
					name += event.text.unicode;
					nameText.setString(name);
				}
				else if(chosen == TypeSeed && seed < 100000000 && event.text.unicode > 47 && event.text.unicode < 58) { //type seed
					seed *= 10;
					seed += (int)event.text.unicode - 48;
					seedText.setString(std::to_string(seed));
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) { //delete char
				if(chosen == TypeName && name.size() > 0) { //delete char from name
					name.pop_back();
					nameText.setString(name);
				}
				else if(chosen == TypeSeed) {//delete char from seed
					seed /= 10;
					seedText.setString(std::to_string(seed));
				}
			}
			else if((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isMouseCoveringShape(nameBackground)) || //switch by mouse
			        (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && chosen == TypeSeed)) {//switch by tab
				chosen = TypeName;
			}
			else if((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isMouseCoveringShape(seedBackground)) || //switch by mouse
			        (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && chosen == TypeName)) {//switch by tab
				chosen = TypeSeed;
			}
		}
		window->clear();

		window->draw(dirtBackground);
		window->draw(mainText);

		backButton.draw(*window);
		commandsOptionButton.draw(*window);
		loadWorldButton.draw(*window);
		newWorldButton.draw(*window);

		window->draw(nameBackground);
		window->draw(nameText);

		window->draw(seedBackground);
		window->draw(seedText);

		window->draw(infoText);

		window->draw(worlds);

		window->display();
	}
	return Quit;
}

Menu::Returned Menu::start(void) {
	playTheme();

	//main text
	mainText.setString(L"Kopalne Rzemiosło");
	mainText.setCharacterSize(window->getSize().x / 10);
	mainText.setPosition((window->getSize().x - mainText.getLocalBounds().width) / 2, 100);

	//version text
	sf::Text versionText(version, font, window->getSize().x / 48);
	versionText.setOutlineThickness(1);
	versionText.setOutlineColor(sf::Color::Black);
	versionText.setFillColor(sf::Color::Yellow);
	versionText.setPosition(mainText.getPosition().x + mainText.getLocalBounds().width - versionText.getLocalBounds().width / 2,
	                        mainText.getPosition().y + mainText.getLocalBounds().height - versionText.getLocalBounds().height / 2);
	versionText.setRotation(-45);

	//buttons
	Button infoButton(window->getSize().x / 2 - 250, window->getSize().y / 2 + 125, 500, 100, "Credits");
	Button optionsButton(window->getSize().x / 2 - 250, window->getSize().y / 2 + 250, 237.5, 100, "Options");
	Button playButton(window->getSize().x / 2 - 250, window->getSize().y / 2, 500, 100, "Play");
	Button quitButton(window->getSize().x / 2 + 12.5, window->getSize().y / 2 + 250, 237.5, 100, "Quit");

	while(window->isOpen()) {
		while(window->pollEvent(event)) {
			if(event.type == event.Closed) {
				window->close();
			}
			else if(playButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return Play;
			}
			else if(infoButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return Info;
			}
			else if(optionsButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return Options;
			}
			else if(quitButton.isCovering() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				window->close();
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) {
				printScreen(*window);
			}
		}
		window->clear();
		window->draw(startBackground);
		window->draw(mainText);
		window->draw(versionText);

		//animation
		if(clock.getElapsedTime().asMilliseconds() > 20) {
			if(animationPage) {
				versionText.setCharacterSize(versionText.getCharacterSize() + 1);
				if(versionText.getCharacterSize() > 40)
					animationPage = false;
			}
			else {
				versionText.setCharacterSize(versionText.getCharacterSize() - 1);
				if(versionText.getCharacterSize() < 30)
					animationPage = true;
			}
			clock.restart();
		}

		infoButton.draw(*window);
		optionsButton.draw(*window);
		playButton.draw(*window);
		quitButton.draw(*window);

		window->display();
	}
	theme.stop();
	return Quit;
}

inline void Menu::playTheme(void) {
	if(soundOption) {
		if(theme.getStatus() != sf::Sound::Playing) {
			theme.play();
		}
	}
	else {
		theme.stop();
	}
	return;
}

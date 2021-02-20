#include "Menu.hpp"

Menu::Menu(sf::RenderWindow &_window) : mainText("", font, 30) {
    window = &_window;
    windowSize = window->getSize();
    halfOfWindowSize.x = windowSize.x / 2;
    halfOfWindowSize.y = windowSize.y / 2;

    if(!themeB.loadFromMemory(menuTheme_ogg, menuTheme_ogg_len))
        exit(-1);
    theme.setBuffer(themeB);
    theme.setVolume(75);
    theme.setLoop(true);

    if(!dirtBackgroundT.loadFromMemory(dirtBackground_png, dirtBackground_png_len))
        exit(-1);
    dirtBackground.setTexture(dirtBackgroundT);
    dirtBackground.setScale(windowSize.x / dirtBackground.getLocalBounds().width,
                            windowSize.y / dirtBackground.getLocalBounds().height);

    if(!startBackgroundT.loadFromMemory(startBackground_png, startBackground_png_len))
        exit(-1);
    startBackground.setTexture(startBackgroundT);
    startBackground.setScale(windowSize.x / startBackground.getLocalBounds().width,
                             windowSize.y / startBackground.getLocalBounds().height);

    mainText.setOutlineThickness(2);
}

Menu::~Menu() {
    theme.stop();
}

Menu::Returned Menu::info(void) {
#define backButton button1
    //main text
    mainText.setString("Game created by: Jacek 'Dobromir'\nTextures created by: Skryty\nGraphic library: SFML created by Laurent Gomila");
    mainText.setCharacterSize(windowSize.x / 24);
    mainText.setPosition(halfOfWindowSize.x - mainText.getLocalBounds().width / 2, 100);

    //buttons
    backButton.create(halfOfWindowSize.x - 250, windowSize.y - 125, 500, 100, "Back");

    while(window->isOpen()) {
        while(window->pollEvent(event)) {
            if(event.type == event.Closed) {
                window->close();
            }
            else if((backButton.clicked()) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
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
#undef backButton
}

Menu::Returned Menu::options(void) {
#define hardExitButton button1
#define loudnessButton button2
#define saveExitButton button3
    playTheme();

    //main text
    mainText.setString("Options");
    mainText.setCharacterSize(windowSize.x / 24);
    mainText.setPosition((windowSize.x - mainText.getLocalBounds().width) / 2, 100);

    //buttons
    hardExitButton.create(halfOfWindowSize.x - 250, windowSize.y - 125, 500, 100, "Exit without saving");
    loudnessButton.create(100, 200, 500, 100, soundOption ? "Set mute" : "Set loud");
    saveExitButton.create(halfOfWindowSize.x - 250, windowSize.y - 250, 500, 100, "Save and back");

    //other info
    sf::Text infoText("AWSD - moving\nLMouse - destroy block\nRMouse - put block\nQ - drop item\n\nF12 - screenshot\nESC - pause menu\nF3 - debuging info", font, windowSize.x / 38.4);
    infoText.setPosition(100, 450);

    while(window->isOpen()) {
        while(window->pollEvent(event)) {
            if(event.type == event.Closed) {
                window->close();
            }
            else if(saveExitButton.clicked()) {
                return Save;
            }
            else if(hardExitButton.clicked() || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                return DontSave;
            }
            else if(loudnessButton.clicked()) {
                loudnessButton.setString(soundOption ? "Set loud" : "Set mute");
                soundOption = !soundOption;
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
#undef backButton
#undef hardExitButton
#undef loudnessButton
#undef saveExitButton
}

Menu::Returned Menu::pause(void) {
#define backButton button1
#define saveButton button2
#define saveAndExitButton button3
    sf::Texture backgroundT;
    sf::Sprite background;
    sf::Color backgroundColor;

    backgroundT.create(windowSize.x, windowSize.y);
    backgroundT.update(*window);

    background.setTexture(backgroundT);
    backgroundColor = background.getColor();
    backgroundColor.a = 150;
    background.setColor(backgroundColor);

    backButton.create(halfOfWindowSize.x - 250, halfOfWindowSize.y, 500, 100, "Back to game");
    saveButton.create(halfOfWindowSize.x - 250, halfOfWindowSize.y + 125, 500, 100, "Save game");
    saveAndExitButton.create(halfOfWindowSize.x - 250, halfOfWindowSize.y + 250, 500, 100, "Save and exit");

    while(window->isOpen()) {
        while(window->pollEvent(event)) {
            if(event.type == event.Closed) {
                window->close();
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || backButton.clicked()) {
                window->pollEvent(event);
                return Back;
            }
            else if(saveButton.clicked()) {
                return Save;
            }
            else if(saveAndExitButton.clicked()) {
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
#undef backButton
#undef saveButton
#undef saveAndExitButton
}

Menu::Returned Menu::play(World &world) {
#define backButton button1
#define deleteButton button2
#define newWorldButton button3
#define godButton button4
#define playButton button5
    //main text
    mainText.setString("Worlds");
    mainText.setCharacterSize(windowSize.x / 24);
    mainText.setPosition(halfOfWindowSize.x - mainText.getLocalBounds().width / 2, 100);

    //getting list of worlds
    std::vector<std::string>worldsNames;
    struct dirent *entry = nullptr;
    DIR *dp = opendir("./saves/");
    if(dp != nullptr) {
        while((entry = readdir(dp))) {
            if(entry->d_name[0] != '.')
                worldsNames.push_back(entry->d_name);
        }
    }
    closedir(dp);
    std::sort(worldsNames.begin(), worldsNames.end());
    sf::Text worldsNamesT("", font, 50);

    //current
    std::vector<std::string>::iterator current = worldsNames.begin();

    sf::Texture currentPtrT;
    currentPtrT.loadFromMemory(currentWorldPtr_png, currentWorldPtr_png_len);

    sf::RectangleShape currentPtr(sf::Vector2f(64, 64));
    currentPtr.setPosition(windowSize.x * 0.1, windowSize.y * 0.2);
    currentPtr.setTexture(&currentPtrT);
    currentPtr.setFillColor(sf::Color(90, 90, 90, 200));

    //worlds list background
    sf::RectangleShape worldsBack(sf::Vector2f(windowSize.x * 0.8, windowSize.y * 0.6));
    worldsBack.setPosition(windowSize.x * 0.1, windowSize.y * 0.2);
    worldsBack.setFillColor(sf::Color(39, 24, 00, 100));

    //line between worlds
    sf::RectangleShape line(sf::Vector2f(worldsBack.getSize().x, 3));
    line.setPosition(windowSize.x * 0.1, windowSize.y);
    line.setFillColor(sf::Color::Black);

    //buttons
    backButton.create(windowSize.x * 0.7, windowSize.y * 0.8, windowSize.x * 0.2, 75, "Back");
    deleteButton.create(windowSize.x * 0.5, windowSize.y * 0.8, windowSize.x * 0.2, 75, "Delete");
    newWorldButton.create(windowSize.x * 0.3, windowSize.y * 0.8, windowSize.x * 0.2, 75, "New world");
    godButton.create(windowSize.x * 0.82, windowSize.y * 0.89, windowSize.x * 0.08, windowSize.y * 0.1, "Not god");
    playButton.create(windowSize.x * 0.1, windowSize.y * 0.8, windowSize.x * 0.2, 75, "Play");

    //Name input
    sf::Text nameInfo("Name:", font, 50);
    nameInfo.setPosition(windowSize.x * 0.1, windowSize.y * 0.89);
    TextInput name(nameInfo.getPosition().x + nameInfo.getLocalBounds().width + 10, windowSize.y * 0.89, windowSize.x * 0.31, 75, TextInput::Type::Text);

    //Seed input
    sf::Text seedInfo("Seed:", font, 50);
    seedInfo.setPosition(nameInfo.getPosition().x + nameInfo.getLocalBounds().width + 20 + windowSize.x * 0.31, windowSize.y * 0.89);
    TextInput seed(seedInfo.getPosition().x + seedInfo.getLocalBounds().width + 10, windowSize.y * 0.89, windowSize.x * 0.25, 75, TextInput::Type::Number);

    while(window->isOpen()) {
        while(window->pollEvent(event)) {
            if(event.type == event.Closed) {
                window->close();
            }
            else if((backButton.clicked()) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {//Back
                return Back;
            }
            else if(deleteButton.clicked() && worldsNames.size() > 0) {//Delete
#ifdef _WIN32
                rmdir(std::string("saves\\" + *current).c_str());
#else
                systemStatus = system(std::string("rm -rf saves/" + *current + " 2> /dev/null").c_str());
#endif // _WIN32
                worldsNames.erase(current);
            }
            else if(newWorldButton.clicked() && name.getString() != "") {//newWorld
                std::fstream file("saves/" + name.getString() + "/world.sav", std::ios::in | std::ios::binary);
                if(!file.good()) {
                    file.close();
                    world.setName(name.getString());
                    try {
                        world.setSeed(std::stoi(seed.getString()));
                    }
                    catch(...) {
                        world.setSeed(0);
                    }
                    return NewWorld;
                }
                file.close();
            }
            else if(godButton.clicked()) {//God
                world.setAllowCommands(!world.getAllowCommands());
                godButton.setString(world.getAllowCommands() ? "God" : "Not god");
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || (playButton.clicked() && worldsNames.size() > 0)) {//Play
                //TOTHINK what if world was deleted after dir searching?
                world.setName(*current);
                return LoadWorld;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) {
                printScreen(*window);
            }
            if(event.type == event.TextEntered) {
                name.input(event);
                seed.input(event);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if(current > worldsNames.begin())
                    current--;
                else
                    current = worldsNames.end() - 1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if(current + 1 < worldsNames.end())
                    current++;
                else
                    current = worldsNames.begin();
            }
        }
        window->clear();
        window->draw(dirtBackground);

        window->draw(mainText);
        window->draw(worldsBack);
        backButton.draw(*window);
        deleteButton.draw(*window);
        newWorldButton.draw(*window);
        godButton.draw(*window);
        playButton.draw(*window);

        name.draw(*window);
        window->draw(nameInfo);
        seed.draw(*window);
        window->draw(seedInfo);

        //TODO do drop down list
        for(uint i = 0; i < worldsNames.size() && i < 8; i++) {
            worldsNamesT.setString(worldsNames[i]);
            worldsNamesT.setPosition(windowSize.x * 0.15, windowSize.y * 0.2 + i * currentPtr.getLocalBounds().height);
            window->draw(worldsNamesT);

            line.setPosition(line.getPosition().x, worldsNamesT.getPosition().y);
            if(i > 0)
                window->draw(line);
            if(*current == worldsNames[i]) {
                currentPtr.setPosition(windowSize.x * 0.1, worldsNamesT.getPosition().y);
            }
        }

        window->draw(currentPtr);

        window->display();
    }
    return Quit;
#undef backButton
#undef deleteButton
#undef newWorldButton
#undef godButton
#undef playButton
}

Menu::Returned Menu::start(void) {
#define infoButton button1
#define optionsButton button2
#define playButton button3
#define quitButton button4
    playTheme();

    //main text
    mainText.setString(L"Kopalne Rzemiosło");
    mainText.setCharacterSize(windowSize.x / 10);
    mainText.setPosition((windowSize.x - mainText.getLocalBounds().width) / 2, 100);

    //version text
    sf::Text versionText(version, font, windowSize.x / 48);
    versionText.setOutlineThickness(1);
    versionText.setOutlineColor(sf::Color::Black);
    versionText.setFillColor(sf::Color::Yellow);
    versionText.setPosition(mainText.getPosition().x + mainText.getLocalBounds().width - versionText.getLocalBounds().width / 2 - 10,
                            mainText.getPosition().y + mainText.getLocalBounds().height - versionText.getLocalBounds().height / 2);
    versionText.setRotation(-45);

    //buttons
    infoButton.create(halfOfWindowSize.x - 250, halfOfWindowSize.y + 125, 500, 100, "Credits");
    optionsButton.create(halfOfWindowSize.x - 250, halfOfWindowSize.y + 250, 237.5, 100, "Options");
    playButton.create(halfOfWindowSize.x - 250, halfOfWindowSize.y, 500, 100, "Play");
    quitButton.create(halfOfWindowSize.x + 12.5, halfOfWindowSize.y + 250, 237.5, 100, "Quit");

    while(window->isOpen()) {
        while(window->pollEvent(event)) {
            if(event.type == event.Closed) {
                window->close();
            }
            else if(playButton.clicked()) {
                return Play;
            }
            else if(infoButton.clicked()) {
                return Info;
            }
            else if(optionsButton.clicked()) {
                return Options;
            }
            else if(quitButton.clicked()) {
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
        if(clock.getElapsedTime().asMilliseconds() > 30) {
            if(animationPage) {
                versionText.setCharacterSize(versionText.getCharacterSize() + 1);
                if(versionText.getCharacterSize() > 50)
                    animationPage = false;
            }
            else {
                versionText.setCharacterSize(versionText.getCharacterSize() - 1);
                if(versionText.getCharacterSize() < 35)
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
#undef infoButton
#undef optionsButton
#undef playButton
#undef quitButton
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
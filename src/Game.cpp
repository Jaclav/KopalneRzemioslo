#include "Game.hpp"

#define mouseInWorldX (sf::Mouse::getPosition().x + view.getCenter().x - window->getSize().x / 2 ) / 64
#define mouseInWorldY (sf::Mouse::getPosition().y + view.getCenter().y - window->getSize().y / 2 ) / 64

Game::Game(sf::RenderWindow &_window, World &_world) : dropped(), items(1), breaking(100), consoleText("\n>", font, 30) {
    window = &_window;

    world = &_world;
    view = window->getView();

    crafting = new Crafting(*window);
    player = new Player(*world);

    sf::Texture breakingT;
    if(!breakingT.loadFromMemory(breaking1_png, breaking1_png_len))
        exit(-1);
    breaking.add(breakingT);
    if(!breakingT.loadFromMemory(breaking2_png, breaking2_png_len))
        exit(-1);
    breaking.add(breakingT);
    if(!breakingT.loadFromMemory(breaking3_png, breaking3_png_len))
        exit(-1);
    breaking.add(breakingT);
    if(!breakingT.loadFromMemory(breaking4_png, breaking4_png_len))
        exit(-1);
    breaking.add(breakingT);
    if(!breakingT.loadFromMemory(breaking5_png, breaking5_png_len))
        exit(-1);
    breaking.add(breakingT);
    if(!breakingT.loadFromMemory(breaking6_png, breaking6_png_len))
        exit(-1);
    breaking.add(breakingT);

    if(!mntBackgroundT.loadFromMemory(mntBackground_png, mntBackground_png_len))
        exit(-1);
    mntBackground.setTexture(mntBackgroundT);
    mntBackground.setScale(window->getSize().x / mntBackground.getLocalBounds().width,
                           window->getSize().y / mntBackground.getLocalBounds().height);

    if(!diggingB.loadFromMemory(digging_ogg, digging_ogg_len))
        exit(-1);
    digging.setBuffer(diggingB);

    if(!puttingB.loadFromMemory(putting_ogg, putting_ogg_len))
        exit(-1);
    putting.setBuffer(puttingB);
    putting.setVolume(10);

    consoleBackground.setSize(sf::Vector2f(500, 200));
    consoleBackground.setFillColor(sf::Color(50, 50, 50, 150));
}

Game::~Game() {
    delete crafting;
    delete player;

    digging.stop();
    putting.stop();
}

Game::Returned Game::play(Menu &menu) {
    uint drawFromX = 0, drawFromY = 0, drawToX = 0, drawToY = 0;

    sf::Text debugText("", font, 50);

    player->load(world->getName());
    dropped.load(world->getName());
    view.setCenter(player->getPosition());

    while(window->isOpen()) {
        while(window->pollEvent(event)) {
            if(event.type == event.Closed) {
                window->close();
            }
            //moving player
            if(!showConsole && !crafting->getShowing() && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                if(player->getPosition().y > 0)
                    player->move(Player::Up);
                window->pollEvent(event);
                break;
            }
            if(!showConsole && !crafting->getShowing() && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if(player->getPosition().y / 64 + 2 < world->getSize().y)
                    player->move(Player::Down);
                window->pollEvent(event);
                break;
            }
            if(!showConsole && !crafting->getShowing() && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                if(player->getPosition().x > 0)
                    player->move(Player::Left);
                window->pollEvent(event);
                break;
            }
            if(!showConsole && !crafting->getShowing() && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if(player->getPosition().x / 64 + 1 < world->getSize().x)
                    player->move(Player::Right);
                window->pollEvent(event);
                break;
            }
            //mouse
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //destroy
                if(mouseInWorldX > 0 && mouseInWorldX < world->getSize().x && mouseInWorldY > 0 && mouseInWorldY < world->getSize().y &&
                        world->operator()(mouseInWorldX, mouseInWorldY) != Items::Bedrock && world->operator()(mouseInWorldX, mouseInWorldY) != Items::Air &&
                        breaking.getStatus() == Animation::Stopped && !canBreak) {
                    breaking.play();
                    breakingMousePos.x = mouseInWorldX;
                    breakingMousePos.y = mouseInWorldY;
                    breaking.sprite.setPosition(breakingMousePos.x * 64, breakingMousePos.y * 64);
                    canBreak = true;
                }
            }
            else {
                breaking.stop();
                canBreak = false;
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) { //put
                if(mouseInWorldX > 0 && mouseInWorldX < world->getSize().x && mouseInWorldY > 0 && mouseInWorldY < world->getSize().y &&
                        world->operator()(mouseInWorldX, mouseInWorldY) == Items::Air && player->inventory.getTypeOfCurrentItem() != Items::Air &&
                        ((uint)mouseInWorldX != player->getPosition().x / 64 || ((uint)mouseInWorldY != player->getPosition().y / 64 &&
                                (uint)mouseInWorldY != player->getPosition().y / 64 + 1))) {
                    if(soundOption)
                        putting.play();
                    world->operator()(mouseInWorldX, mouseInWorldY) =  player->inventory.remove();
                }
                else if(world->operator()(mouseInWorldX, mouseInWorldY) == Items::CraftingTable) {
                    crafting->setShowing(true);
                }
            }
            //crafting
            if(crafting->getShowing() && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                crafting->setShowing(false);
                window->pollEvent(event);
                break;
            }
            //inventory
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
            if(!showConsole && event.type == sf::Event::TextEntered && event.text.unicode > 47 && event.text.unicode < 58) {
                player->inventory.setPtr(event.text.unicode == 48 ? 9 : event.text.unicode - 49);
            }
            //drop
            if(!showConsole && sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && player->inventory.getTypeOfCurrentItem() != Items::Air &&
                    (world->operator()(player->getPosition().x / 64 + (player->getSide() == Player::Right ? 1 : -1), player->getPosition().y / 64) == Items::Air ||
                     world->operator()(player->getPosition().x / 64 + (player->getSide() == Player::Right ? 1 : -1), player->getPosition().y / 64) == Items::Grass)) {//check if can be dropped
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {//drop all current items
                    dropped.drop(player->getPosition().x + (player->getSide() == Player::Right ? 64 : -64),//drop from player's side
                                 player->getPosition().y + 64, player->inventory.getTypeOfCurrentItem(), player->inventory.getQuantityOfCurrentItem());
                    while(player->inventory.remove() != Items::Air);
                }
                else {//drop item
                    dropped.drop(player->getPosition().x + (player->getSide() == Player::Right ? 64 : -64),//drop from player's side
                                 player->getPosition().y + 64, player->inventory.getTypeOfCurrentItem(), 1);
                    player->inventory.remove();
                }
                window->pollEvent(event);
                break;
            }
            //Fs and esc
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
                showDebug = !showDebug;
                window->pollEvent(event);
                break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) {
                printScreen(*window);
            }
            if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                wasEscapeReleased = true;
            }
            if(!crafting->getShowing() && wasEscapeReleased && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type  == event.LostFocus)) {
                wasEscapeReleased = false;
                view.setCenter(window->getSize().x / 2, window->getSize().y / 2);
                window->setView(view);
                window->pollEvent(event);

                returned = menu.pause();

                window->pollEvent(event);

                if(returned != Menu::Back) {//if Save or SaveAndexit
                    world->save();
                    player->save(world->getName());
                    dropped.save(world->getName());
                }
                if(returned == Menu::SaveAndExit) {
                    return Back;
                }

                view.setCenter(player->getPosition());
                window->setView(view);
                break;
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
        }//end of event loop

        if(breaking.getStatus() == Animation::Stopped && canBreak) { //if animation ended an can break block, break block
            if(soundOption)
                digging.play();
            dropped.drop(breakingMousePos.x * 64, breakingMousePos.y * 64, world->operator()(breakingMousePos.x, breakingMousePos.y), 1);
            world->operator()(breakingMousePos.x, breakingMousePos.y) = Items::Air;

            canBreak = false;
        }

        player->update();

        //setting camera position
        if(player->getPosition().x > view.getCenter().x + 128 || player->getPosition().x + 128 < view.getCenter().x ||
                player->getPosition().y > view.getCenter().y + 128 || player->getPosition().y + 128 < view.getCenter().y) {
            if(player->getPosition().x > view.getCenter().x) {
                view.setCenter(view.getCenter().x + 21.333333333, view.getCenter().y);
            }
            if(player->getPosition().x < view.getCenter().x) {
                view.setCenter(view.getCenter().x - 21.333333333, view.getCenter().y);
            }
            if(player->getPosition().y > view.getCenter().y) {
                //TODO: when is falling camera is too far from player
                view.setCenter(view.getCenter().x, view.getCenter().y + 21.333333333);
            }
            if(player->getPosition().y < view.getCenter().y) {
                view.setCenter(view.getCenter().x, view.getCenter().y - 21.333333333);
            }
        }
        window->setView(view);

        //drawing
        window->clear();

        mntBackground.setPosition(view.getCenter().x - window->getSize().x / 2, view.getCenter().y - window->getSize().y / 2);
        window->draw(mntBackground);

        //drawing items
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

        for(uint x = drawFromX; x < drawToX; x++) {
            for(uint y = drawFromY; y < drawToY; y++) {
                items.draw(*window, x * 64, y * 64, (Items::Item) world->operator()(x, y));
            }
        }
        breaking.draw(*window);

        //collecting and drawing dropped items
        plr = dropped.collect(player->getPosition().x, player->getPosition().y + 64);
        if(plr.type != Items::Air) {
            for(uint i = 0; i < plr.quantity; i++)
                player->inventory.add(plr.type);
        }

        dropped.draw(*window, *world);

        //drawing player
        player->draw(*window);

        //drawing crafting table
        crafting->draw(*window, *player);

        //drawing debug info
        if(showDebug) {
            debugText.setString("FPS: " + std::to_string(fpsCounter()) + " X: " + std::to_string(player->getPosition().x / 64) +
                                " Y: " + std::to_string(player->getPosition().y / 64) + " world: " + world->getName());
            debugText.setPosition(view.getCenter().x - window->getSize().x / 2, view.getCenter().y - window->getSize().y / 2);
            window->draw(debugText);
        }

        //drawing console
        if(showConsole) {
            consoleBackground.setPosition(view.getCenter().x - window->getSize().x / 2,
                                          view.getCenter().y + window->getSize().y / 2 - consoleBackground.getSize().y);
            consoleText.setPosition(view.getCenter().x - window->getSize().x / 2 + 10,
                                    view.getCenter().y + window->getSize().y / 2 - 80);
            window->draw(consoleBackground);
            window->draw(consoleText);
        }

        window->display();
    }
    world->save();
    player->save(world->getName());
    dropped.save(world->getName());
    return Quit;
}

void Game::interpreter() {
    if(!world->getAllowCommands()) {
        commandInfo = "Commands aren't allowed!";
        return;
    }

    std::string cmd = command.substr(0, command.find(' '));
    command = command.substr(command.find(' ') + 1, command.size() - command.find(' '));
    std::string p1 = command.substr(0, command.find(' '));
    std::string p2 = command.substr(command.find(' ') + 1, command.size());

    if(cmd == "tp") {
        try {
            player->setPosition(p1 == "@" ? player->getPosition().x : std::stoi(p1) * 64, p2 == "@" ? player->getPosition().y : std::stoi(p2) * 64);
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
        else if(p1 == "craftingTable")
            item = Items::CraftingTable;
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

        try {
            howMany = std::stoi(p2);
        }
        catch(...) {
            howMany = 1;
        }

        for (uint i = 0; i < howMany; i++) {
            if(player->inventory.add(item)) {
                break;//when cannot add more
            }
        }

        commandInfo = "Block added";
        return;
    }
    else if(cmd == "noclip") {
        try {
            world->setNoclip(std::stoi(p1));
        }
        catch(...) {
            commandInfo = "Wrong parameter!";
            return;
        }
        commandInfo = "Noclip setted";
    }
    else if(cmd == "allowCommands") {
        try {
            world->setAllowCommands(std::stoi(p1));
        }
        catch(...) {
            commandInfo = "Wrong parameter!";
            return;
        }
        commandInfo = "AllowCommands setted";
    }
    else if(cmd == "clear") {
        player->inventory.setPtr(0);
        for(uint i = 0; i < 10; i++) {
            while(player->inventory.getQuantityOfCurrentItem() > 0) {
                player->inventory.remove();
            }
            player->inventory.incPtr();
        }
        commandInfo = "Inventory cleared";
    }
    else if(cmd != "") {
        commandInfo = "Unknown command!";
    }
    return;
}

CFLAGS=-pedantic -Wextra -Wall -fexceptions -std=c++2a -Iinclude -c
run:
	mkdir obj
	mkdir obj/src
	g++ $(CFLAGS) main.cpp -o obj/main.o
	g++ $(CFLAGS) src/Button.cpp -o obj/src/Button.o
	g++ $(CFLAGS) src/Console.cpp -o obj/src/Console.o
	g++ $(CFLAGS) src/Game.cpp -o obj/src/Game.o
	g++ $(CFLAGS) src/Ini.cpp -o obj/src/Ini.o
	g++ $(CFLAGS) src/Items.cpp -o obj/src/Items.o
	g++ $(CFLAGS) src/Menu.cpp -o obj/src/Menu.o
	g++ $(CFLAGS) src/Player.cpp -o obj/src/Player.o
	g++ $(CFLAGS) src/tools.cpp -o obj/src/tools.o
	g++ $(CFLAGS) src/World.cpp -o obj/src/World.o
	g++ -o kopalnerzemioslo obj/main.o obj/src/Button.o obj/src/Console.o obj/src/Game.o obj/src/Ini.o obj/src/Items.o obj/src/Menu.o obj/src/Player.o obj/src/tools.o obj/src/World.o  -s -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio

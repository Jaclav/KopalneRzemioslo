CFLAGS=-pedantic -Wextra -Wall -fexceptions -std=c++2a -Iinclude -c
run:
	mkdir obj
	mkdir obj/src
	g++ $(CFLAGS) main.cpp -o obj/Debug/main.o
	g++ $(CFLAGS) src/Button.cpp -o obj/Debug/src/Button.o
	g++ $(CFLAGS) src/Console.cpp -o obj/Debug/src/Console.o
	g++ $(CFLAGS) src/Game.cpp -o obj/Debug/src/Game.o
	g++ $(CFLAGS) src/Ini.cpp -o obj/Debug/src/Ini.o
	g++ $(CFLAGS) src/Items.cpp -o obj/Debug/src/Items.o
	g++ $(CFLAGS) src/Menu.cpp -o obj/Debug/src/Menu.o
	g++ $(CFLAGS) src/Player.cpp -o obj/Debug/src/Player.o
	g++ $(CFLAGS) src/tools.cpp -o obj/Debug/src/tools.o
	g++ $(CFLAGS) src/World.cpp -o obj/Debug/src/World.o
	g++ -o kopalnerzemioslo obj/Debug/main.o obj/Debug/src/Button.o obj/Debug/src/Console.o obj/Debug/src/Game.o obj/Debug/src/Ini.o obj/Debug/src/Items.o obj/Debug/src/Menu.o obj/Debug/src/Player.o obj/Debug/src/tools.o obj/Debug/src/World.o  -s -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio

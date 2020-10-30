COMPILER=g++
CFLAGS=-pedantic -Wextra -Wall -fexceptions -std=c++2a -Iinclude -s -Os -c

run: bin obj obj/main.o obj/src/Button.o obj/src/Console.o obj/src/Game.o obj/src/Ini.o obj/src/Items.o obj/src/Menu.o obj/src/Player.o obj/src/tools.o obj/src/World.o
	$(COMPILER) -o bin/kopalnerzemioslo obj/main.o obj/src/Button.o obj/src/Console.o obj/src/Game.o obj/src/Ini.o obj/src/Items.o obj/src/Menu.o obj/src/Player.o obj/src/tools.o  obj/src/World.o -s -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio

bin:
	mkdir bin

obj:
	mkdir obj
	mkdir obj/src

obj/main.o: main.cpp
	$(COMPILER) $(CFLAGS) main.cpp -o obj/main.o

obj/src/Button.o: src/Button.cpp
	$(COMPILER) $(CFLAGS) src/Button.cpp -o obj/src/Button.o

obj/src/Console.o: src/Console.cpp
	$(COMPILER) $(CFLAGS) src/Console.cpp -o obj/src/Console.o

obj/src/Game.o: src/Game.cpp
	$(COMPILER) $(CFLAGS) src/Game.cpp -o obj/src/Game.o

obj/src/Ini.o: src/Ini.cpp
	$(COMPILER) $(CFLAGS) src/Ini.cpp -o obj/src/Ini.o

obj/src/Items.o: src/Items.cpp
	$(COMPILER) $(CFLAGS) src/Items.cpp -o obj/src/Items.o

obj/src/Menu.o: src/Menu.cpp
	$(COMPILER) $(CFLAGS) src/Menu.cpp -o obj/src/Menu.o

obj/src/Player.o: src/Player.cpp
	$(COMPILER) $(CFLAGS) src/Player.cpp -o obj/src/Player.o

obj/src/tools.o: src/tools.cpp
	$(COMPILER) $(CFLAGS) src/tools.cpp -o obj/src/tools.o

obj/src/World.o: src/World.cpp
	$(COMPILER) $(CFLAGS) src/World.cpp -o obj/src/World.o

clean:
	rm -rf obj
	rm -rf bin

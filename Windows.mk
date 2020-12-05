COMPILER="D:\Informatyka\MinGW-5.1.0\bin\g++.exe"
CFLAGS=-Wfatal-errors -Wextra -Wall -std=c++11 -I$(SFMLPATH)\include -Iinclude\ -s -Os -c

SFMLPATH="D:\Informatyka\SFML-2.5.1"

WINDRES=D:\Informatyka\MinGW-5.1.0\bin\windres.exe
WFLAGS=-J rc -O coff -i

run: bin obj obj\main.o obj\src\Animation.o obj\src\Button.o obj\src\Console.o obj\src\Dropped.o obj\src\Game.o obj\src\Ini.o obj\src\Items.o obj\src\Inventory.o obj\src\Menu.o obj\src\Player.o obj\src\tools.o obj\src\World.o obj\main.res
	$(COMPILER) -o bin\kopalnerzemioslo -mwindows obj\main.o obj\src\Animation.o obj\src\Button.o obj\src\Console.o obj\src\Dropped.o obj\src\Game.o obj\src\Ini.o obj\src\Inventory.o  obj\src\Items.o obj\src\Menu.o obj\src\Player.o obj\src\tools.o obj\src\World.o obj\main.res $(SFMLPATH)\lib\libsfml-audio.a $(SFMLPATH)\lib\libsfml-graphics.a $(SFMLPATH)\lib\libsfml-system.a $(SFMLPATH)\lib\libsfml-window.a

bin:
	mkdir bin

obj:
	mkdir obj
	mkdir obj\src

obj\main.o: main.cpp
	$(COMPILER) $(CFLAGS) main.cpp -o obj\main.o

obj\src\Animation.o: src\Animation.cpp
	$(COMPILER) $(CFLAGS) src\Animation.cpp -o obj\src\Animation.o

obj\src\Button.o: src\Button.cpp
	$(COMPILER) $(CFLAGS) src\Button.cpp -o obj\src\Button.o

obj\src\Console.o: src\Console.cpp
	$(COMPILER) $(CFLAGS) src\Console.cpp -o obj\src\Console.o
	
obj\src\Dropped.o: src\Dropped.cpp
	$(COMPILER) $(CFLAGS) src\Dropped.cpp -o obj\src\Dropped.o

obj\src\Game.o: src\Game.cpp
	$(COMPILER) $(CFLAGS) src\Game.cpp -o obj\src\Game.o

obj\src\Ini.o: src\Ini.cpp
	$(COMPILER) $(CFLAGS) src\Ini.cpp -o obj\src\Ini.o

obj\src\Inventory.o: src\Inventory.cpp
	$(COMPILER) $(CFLAGS) src\Inventory.cpp -o obj\src\Inventory.o

obj\src\Items.o: src\Items.cpp
	$(COMPILER) $(CFLAGS) src\Items.cpp -o obj\src\Items.o

obj\src\Menu.o: src\Menu.cpp
	$(COMPILER) $(CFLAGS) src\Menu.cpp -o obj\src\Menu.o

obj\src\Player.o: src\Player.cpp
	$(COMPILER) $(CFLAGS) src\Player.cpp -o obj\src\Player.o

obj\src\tools.o: src\tools.cpp
	$(COMPILER) $(CFLAGS) src\tools.cpp -o obj\src\tools.o

obj\src\World.o: src\World.cpp
	$(COMPILER) $(CFLAGS) src\World.cpp -o obj\src\World.o

obj\main.res: main.rc
	$(WINDRES) $(WFLAGS) main.rc -o obj\main.res

clean:
	rmdir /S /Q obj
	rmdir /S /Q bin

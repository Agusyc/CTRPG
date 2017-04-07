main:
	mkdir -p bin
	g++ -Wall `pkg-config --libs ncurses jsoncpp --cflags ncurses jsoncpp` -o bin/CTRPG src/*.cpp

debug:
	mkdir -p bin
	g++ -Wall -g `pkg-config --libs ncurses jsoncpp --cflags ncurses jsoncpp` -o bin/CTRPG src/*.cpp

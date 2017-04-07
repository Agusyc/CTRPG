main:
	g++ -Wall `pkg-config --libs ncurses jsoncpp --cflags ncurses jsoncpp` -o bin/CTRPG src/*.cpp

debug:
	g++ -Wall -g `pkg-config --libs ncurses jsoncpp --cflags ncurses jsoncpp` -o bin/CTRPG src/*.cpp

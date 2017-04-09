main:
	mkdir -p bin
	g++ -Wall -std=c++11 `pkg-config --libs jsoncpp --cflags jsoncpp` -o bin/CTRPG src/*.cpp

debug:
	mkdir -p bin
	g++ -Wall -g -std=c++11 `pkg-config --libs jsoncpp --cflags jsoncpp` -o bin/CTRPG src/*.cpp

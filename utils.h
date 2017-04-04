#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <string>

#define SLOW_TEXT 200
#define NORMAL_TEXT 65
#define QUICK_TEXT 35

using namespace std;


void printMessage(string message, int time = NORMAL_TEXT, int extraTime = 0, bool newLine = true);

void newLine();

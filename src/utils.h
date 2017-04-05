#pragma once

#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <limits>

// Predefined text speeds
#define SLOW_TEXT 200
#define NORMAL_TEXT 65
#define QUICK_TEXT 35

// Prints message with a certain speed and waits some time for the next message
void printMessage(std::string message, int time = NORMAL_TEXT, int extraTime = 300, bool newLine = true);

// Clears the terminal, waiting some time before doing it (To let the user read the actual contents)
void clearScreen(int waitTime = 1000);

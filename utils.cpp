#include "utils.h"

void printMessage(string message, int time, int extraTime, bool newLine) {
  for (unsigned int i = 0; i < message.length(); i++) {
    cout << message.at(i);
    fflush(stdout);
    usleep(time * 1000);
  }

  if (newLine)
    cout << endl;

  if (extraTime != 0) {
    usleep(extraTime * 1000);
  }
}

void clearScreen(int waitTime) {
  usleep(waitTime * 1000);
  cout << "\033[2J\033[1;1H";
}

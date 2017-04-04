#include "battle.h"

Player player;
Enemy enemy;

void init() {
  enemy.name = "testing name lol xd";
}

int main() {
  init();

  printMessage("Welcome to CTRPG!");

  Battle testBattle(enemy, player);

  testBattle.start("This is a test!");

  return 0;
}

#include "battle.h"

Player player = {
	"Agus",
	1,
	1,
	0,
	0,
	10,
	1,
	0
};

Enemy enemy = {
	"testing name lol",
	1,
	1,
	0,
	10
};

void init() {
  Attack attack = {
	"Little punch",
	1,
	0
  };

  player.attacks.push_back(attack);
}

int main() {
  init();

  printMessage("Welcome to CTRPG!");

  Battle testBattle(enemy, player);

  testBattle.start("This is a test!");

  return 0;
}

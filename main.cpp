#include "battle.h"

Player player = {
	"Agus",
	1,
	1,
	0,
	0,
	10,
	1,
	0,
	10
};

Enemy enemy = {
	"Badass enemy (Not really)",
	1,
	1,
	0,
	10,
	10
};

void init() {
  Attack littlePunch = {
	"Little punch",
	3,
	0
  };

  player.attacks.push_back(littlePunch);

  Attack superPunch = {
	"Super punch",
	2,
	0
  };

  enemy.attacks.push_back(superPunch);

  Attack superLaserBeam  = {
	"Super laser beam",
	0,
	5
  };

  enemy.attacks.push_back(superLaserBeam);

}

int main() {
  init();

  printMessage("Welcome to CTRPG!");

  Battle testBattle(enemy, player);

  testBattle.start("This is a test!");

  return 0;
}

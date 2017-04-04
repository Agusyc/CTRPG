#include "battle.h"

Player player = {
  "Agus", // name
  1, // attack
  1, // defense
  1, // shieldDefense
  0, // mana
  0, // stamina
  10, // hp
  1, //level 
  0, // xp
  10 // goal
};

Enemy enemy = {
  "Badass guy", // name
  1, // attack
  1, // defense
  1, // shieldDefense
  0, // stamina
  10, // hp
  10 // xp
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

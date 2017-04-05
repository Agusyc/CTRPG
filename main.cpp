#include "battle.h"

using namespace std;

// This struct represents the player's character
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

// Enemy, for testing purposes only
Enemy enemy = {
  "Badass guy", // name
  1, // attack
  1, // defense
  1, // shieldDefense
  0, // stamina
  10, // hp
  10 // xp
};

// Initializes eveything
void init() {
  Attack littlePunch = {
    "Little Punch",
    3,
    0
  };
  
  player.attacks.push_back(littlePunch);
  
  Attack superPunch = {
    "Super Punch",
    2,
    0
  };
  
  enemy.attacks.push_back(superPunch);
  
  Attack superLaserBeam  = {
    "Super Laser Beam",
    0,
    5
  };
  
  enemy.attacks.push_back(superLaserBeam);
  
}

int main() {
  init();
  
  printMessage("Welcome to CTRPG!");

  // Just for testing the battle system
  Battle testBattle(enemy, player);
  
  testBattle.start("This is a test!");
  
  return 0;
}

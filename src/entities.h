#pragma once

#include <string>
#include <vector>

// This struct represents an attack
struct Attack {
  std::string name;
  int damage, magicDamage;
};

// This struct represents an enemy
struct Enemy {
  std::string name;
  int attack, defense, shieldDefense, stamina, hp, xp;
  std::vector<Attack> attacks;
};

// This struct is used only once, and represents the player.
struct Player {
  std::string name;
  int attack, defense, shieldDefense, mana, stamina, hp, level, xp, goal;
  std::vector<Attack> attacks;
};

// TODO: Make an Item struct

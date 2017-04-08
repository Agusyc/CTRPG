#pragma once

#include <string>
#include <vector>

// This struct represents an attack
struct Attack {
  std::string name;
  int damage, magicDamage, mana, stamina;
};

// This struct represents an enemy
struct Enemy {
  std::string name;
  int attack, defense, shieldDefense, mana, stamina, hp, xp, id, minLevel, maxLevel;
  std::vector<Attack> attacks;
};

// This struct is used only once, and represents the player.
struct Player {
  std::string name;
  int attack, defense, shieldDefense, mana, stamina, hp, level, xp, goal;
  std::vector<Attack> attacks;
};

// This struct represents an item
struct Item {
  std::string name;
  int attackBoost, defenseBoos, manaRecover, hpRecover, minLevel, maxLevel;
};

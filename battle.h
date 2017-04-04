#include "utils.h"
#include <string>
#include <vector>
#include <sstream>

struct Enemy {
  string name;
  int attack, defense, stamina, hp, xp;
};

struct Attack {
  string name;
  int damage, magicDamage;
};

struct Player {
  string name;
  int attack, defense, mana, stamina, hp, level, xp, goal;
  vector<Attack> attacks;
};

class Battle {
 private:
  Player player;
  Enemy enemy;
  void loop();
  void attack();
  int showMenu();
  bool over = false;
  bool playerTurn = true;
  bool defending = false;
 public:
  Battle(Enemy enm, Player ply);
  void start(string message);
};

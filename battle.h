#include "utils.h"

struct Enemy {
  string name;
  int attack, defense, stamina, hp;
};

struct Attack {
  string name;
  int damage, magicDamage;
};

struct Player {
  string name;
  int attack, defense, mana, stamina, hp, level, xp;
  Attack[] attacks;
};

class Battle {
 private:
  Player player;
  Enemy enemy;
  void loop();
  void attack(Attack attack);
  void showMenu();
  bool over = false;
  bool playerTurn = true;
 public:
  Battle(Enemy enm, Player ply);
  void start(string message);
};

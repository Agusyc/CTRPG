#include "utils.h"
#include "objects.h"
#include "jsonparser.h"
#include <json/writer.h>
#include <sstream>
#include <random>

class Battle {
 private:
  Player player;
  Enemy enemy;
  void loop();
  void attack();
  int showMenu();
  void showLevelUpMenu(Player player);
  bool over = false;
  bool playerTurn = true;
  bool defending = false;
 public:
  Battle(Enemy enm, Player ply);
  Player start(std::string message);
};

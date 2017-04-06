#include "utils.h"
#include "entities.h"
#include "entityparser.h"
#include <json/writer.h>
#include <sstream>

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
  void start(std::string message);
};

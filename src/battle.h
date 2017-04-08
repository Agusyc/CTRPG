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
  int attack();
  int showMenu();
  int useItem();
  void showLevelUpMenu(Player player);
  void writeItems();
  bool over = false;
  bool playerTurn = true;
  bool defending = false;
 public:
  Battle(Enemy enm, Player ply);
  Player start(std::string message);
};

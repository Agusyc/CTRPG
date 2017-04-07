#include "entityparser.h"

using namespace std;

Json::Value getJsonPlayer() {
  Json::Value jPlayer;

  Json::Reader reader; // The reader... that reads

  ifstream ifs("./json/player.json");

  bool parsingSuccessful = reader.parse(ifs, jPlayer);
  if (!parsingSuccessful) {
    // Print error
    cout << "Failed to parse the player" << endl
          << reader.getFormattedErrorMessages();
  }

  return jPlayer;
}

int getEnemiesNumber() {
	  Json::Value root;

  Json::Reader reader; // The reader... that reads

  ifstream ifs("./json/enemies.json");

  bool parsingSuccessful = reader.parse(ifs, root);
  if (!parsingSuccessful) {
    // Print error
    cout << "Failed to parse the enemies" << endl
          << reader.getFormattedErrorMessages();
  }

  return root.size();
}

Attack parseAttack(int index) {
  Json::Value root; // The root element
  Json::Reader reader; // The reader... that reads

  ifstream ifs("./json/attacks.json");

  bool parsingSuccessful = reader.parse(ifs, root);
  if (!parsingSuccessful) {
    // Print error
    cout << "Failed to parse the attacks" << endl
	  << reader.getFormattedErrorMessages();
  }

  Json::Value jAttack = root[index];

  Attack attack;

  attack.name = jAttack["name"].asString();
  attack.damage = jAttack["damage"].asInt();
  attack.magicDamage = jAttack["magicDamage"].asInt();
  attack.mana = jAttack["mana"].asInt();
  attack.stamina = jAttack["stamina"].asInt();

  return attack;
}

Enemy parseEnemy(int index) {
  Json::Value root; // The root element
  Json::Reader reader; // The reader... that reads

  ifstream ifs("./json/enemies.json");

  bool parsingSuccessful = reader.parse(ifs, root);
  if (!parsingSuccessful) {
    // Print error
    cout << "Failed to parse the enemies" << endl
          << reader.getFormattedErrorMessages();
  }

  Json::Value jEnemy = root[index];

  Enemy enemy;

  enemy.name = jEnemy["name"].asString();
  enemy.attack = jEnemy["attack"].asInt();
  enemy.defense = jEnemy["defense"].asInt();
  enemy.shieldDefense = jEnemy["shieldDefense"].asInt();
  enemy.mana = jEnemy["mana"].asInt();
  enemy.stamina = jEnemy["stamina"].asInt();
  enemy.hp = jEnemy["hp"].asInt();
  enemy.xp = jEnemy["xp"].asInt();

  // Iterates trough the array "attacks", which contains all the indexes of the attacks of the enemy
  for (const Json::Value& attack : jEnemy["attacks"]) {
    enemy.attacks.push_back(parseAttack(attack.asInt())); // Pushes the attack to the vector
  }

  return enemy;
}

Player parsePlayer() {
  Json::Value jPlayer; // The root element
  Json::Reader reader; // The reader... that reads

  ifstream ifs("./json/player.json");

  bool parsingSuccessful = reader.parse(ifs, jPlayer);
  if (!parsingSuccessful) {
    // Print error
    cout << "Failed to parse the player" << endl
          << reader.getFormattedErrorMessages();
  }

  Player player;

  player.name = jPlayer["name"].asString();
  player.attack = jPlayer["attack"].asInt();
  player.defense = jPlayer["defense"].asInt();
  player.shieldDefense = jPlayer["shieldDefense"].asInt();
  player.mana = jPlayer["mana"].asInt();
  player.stamina = jPlayer["stamina"].asInt();
  player.hp = jPlayer["hp"].asInt();
  player.xp = jPlayer["xp"].asInt();
  player.level =jPlayer["level"].asInt();
  player.goal = jPlayer["goal"].asInt();

  // Iterates trough the array "attacks", which contains all the indexes of the attacks of the player
  for (const Json::Value& attack : jPlayer["attacks"]) { // "attack" is the current index
    player.attacks.push_back(parseAttack(attack.asInt())); // Pushes the attack to the vector
  }

  return player;
}

#include "entityparser.h"

using namespace std;

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

  Attack attack;

  attack.name = root[index]["name"];
  attack.damage = root[index]["damage"];
  attack.magicDamage = root[index]["magicDamage"];

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

  enemy.name = jEnemy["name"];
  enemy.attack = jEnemy["attack"];
  enemy.defense = jEnemy["defense"];
  enemy.shieldDefense = jEnemy["shieldDefense"];
  enemy.stamina = jEnemy["stamina"];
  enemy.hp = jEnemy["hp"];
  enemy.xp = jEnemy["xp"];

  for (int i = 0; i < jEnemy["attacks"].size(); i++) {
  	enemy.attacks.push_back(parseAttack(jEnemy["attacks"][i]));
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

  player.name = jPlayer["name"];
  player.attack = jPlayer["attack"];
  player.defense = jPlayer["defense"];
  player.shieldDefense = jPlayer["shieldDefense"];
  player.mana = jPlayer["mana"];
  player.stamina = jPlayer["stamina"];
  player.hp = jPlayer["hp"];
  player.xp = jPlayer["xp"];
  player.level =jPlayer["level"];
  player.goal = jPlayer["goal"];

  for (int i = 0; i < jPlayer["attacks"].size(); i++) {
        player.attacks.push_back(parseAttack(jPlayer["attacks"][i]));
  }

  return player;
}

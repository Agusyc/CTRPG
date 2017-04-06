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

  attack.name = root[index]["name"].asString();
  attack.damage = root[index]["damage"].asInt();
  attack.magicDamage = root[index]["magicDamage"].asInt();

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
  enemy.stamina = jEnemy["stamina"].asInt();
  enemy.hp = jEnemy["hp"].asInt();
  enemy.xp = jEnemy["xp"].asInt();

  for (unsigned int i = 0; i < jEnemy["attacks"].size(); i++) {
  	enemy.attacks.push_back(parseAttack(jEnemy["attacks"][i].asInt()));
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

  for (unsigned int i = 0; i < jPlayer["attacks"].size(); i++) {
        player.attacks.push_back(parseAttack(jPlayer["attacks"][i].asInt()));
  }

  return player;
}

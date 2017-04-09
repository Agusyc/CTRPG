#include "jsonparser.h"

using namespace std;

Json::Value getJsonPlayer() {
    Json::Value jPlayer;

    Json::Reader reader; // The reader... that reads

    ifstream ifs("./json/player.json");

    bool parsingSuccessful = reader.parse(ifs, jPlayer);
    if (!parsingSuccessful) {
        // Print error
        cout << "Failed to parse the player" << endl << reader.getFormattedErrorMessages();
        exit(1);
    }

    return jPlayer;
}

int getAttacksNumber() {
    Json::Value attacks;

    Json::Reader reader; //The reader... that reads

    ifstream ifs("./json/attacks.json");

    bool parsingSuccessful = reader.parse(ifs, attacks);
    if (!parsingSuccessful) {
        // Print error
        cout << "Failed to parse the enmies." << endl << "Error:" << endl << reader.getFormattedErrorMessages();
        exit(1);
    }

    return attacks.size();
}

int getItemsNumber() {
    Json::Value items;

    Json::Reader reader; // The reader... that reads

    ifstream ifs("./json/enemies.json");

    bool parsingSuccessful = reader.parse(ifs, items);
    if (!parsingSuccessful) {
        // Print error
        cout << "Failed to parse the enemies." << endl << "Error:" << endl << reader.getFormattedErrorMessages();
        exit(1);
    }

    return items.size();
}

int getEnemiesNumber() {
    Json::Value enemies;

    Json::Reader reader; // The reader... that reads

    ifstream ifs("./json/enemies.json");

    bool parsingSuccessful = reader.parse(ifs, enemies);
    if (!parsingSuccessful) {
        // Print error
        cout << "Failed to parse the enemies." << endl << "Error:" << endl << reader.getFormattedErrorMessages();
    }

    return enemies.size();
}

Item parseItem(int index) {
    Json::Value root; // The root element
    Json::Reader reader; // The reader... that reads

    ifstream ifs("./json/items.json");

    bool parsingSuccessful = reader.parse(ifs, root);
    if(!parsingSuccessful) {
        // Print error
        cout << "Failed to parse the attacks." << endl << "Error:" << endl << reader.getFormattedErrorMessages();
        exit(1);
    }

    Json::Value jItem = root[index];

    Item item;

    item.name = jItem["name"].asString();
    item.attackBoost = jItem["attackBoost"].asInt();
    item.defenseBoost = jItem["defenseBoost"].asInt();
    item.manaRecover = jItem["manaRecover"].asInt();
    item.staminaRecover = jItem["staminaRecover"].asInt();
    item.hpRecover = jItem["hpRecover"].asInt();
    item.minLevel = jItem["minLevel"].asInt();
    item.maxLevel = jItem["maxLevel"].asInt();
    item.id = index;

    return item;
}

Attack parseAttack(int index) {
    Json::Value root; // The root element
    Json::Reader reader; // The reader... that reads

    ifstream ifs("./json/attacks.json");

    bool parsingSuccessful = reader.parse(ifs, root);
    if (!parsingSuccessful) {
        // Print error
        cout << "Failed to parse the attacks." << endl << "Error:" << endl << reader.getFormattedErrorMessages();
        exit(1);
    }

    Json::Value jAttack = root[index];

    Attack attack;

    attack.name = jAttack["name"].asString();
    attack.damage = jAttack["damage"].asInt();
    attack.magicDamage = jAttack["magicDamage"].asInt();
    attack.mana = jAttack["mana"].asInt();
    attack.stamina = jAttack["stamina"].asInt();
    attack.minLevel = jAttack["minLevel"].asInt();
    attack.maxLevel = jAttack["maxLevel"].asInt();
    attack.cost = jAttack["cost"].asInt();
    attack.id = index;

    return attack;
}

Enemy parseEnemy(int index) {
    Json::Value root; // The root element
    Json::Reader reader; // The reader... that reads

    ifstream ifs("./json/enemies.json");

    bool parsingSuccessful = reader.parse(ifs, root);
    if (!parsingSuccessful) {
        // Print error
        cout << "Failed to parse the enemies." << endl << "Error:" << endl << reader.getFormattedErrorMessages();
        exit(1);
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
    enemy.id = index;
    enemy.minLevel = jEnemy["minLevel"].asInt();
    enemy.maxLevel = jEnemy["maxLevel"].asInt();

    // Iterates trough the array "attacks", which contains all the indexes of the attacks of the enemy
    for (const Json::Value& attack : jEnemy["attacks"]) {
        enemy.attacks.push_back(parseAttack(attack.asInt())); // Pushes the attack to the vector
    }

    return enemy;
}

Player parsePlayer() {
    Json::Value jPlayer; // The root element

    Player player; // The "Player" struct

    struct stat buffer;
    if(stat("./json/player.json", &buffer) == 0) {
        // File exists

        ifstream ifs("./json/player.json");

        Json::Reader reader; // The reader... that reads.

        bool parsingSuccessful = reader.parse(ifs, jPlayer);
        if (!parsingSuccessful) {
            // Print error
            cout << "Failed to parse the player." << endl << "Error:" << endl << reader.getFormattedErrorMessages();
        }

    } else {
        // The player doesn't exist.
        cout << "Welcome to CTRPG! Please enter your name: ";
        string name;

        cin >> name;

        // We create a new player.

        jPlayer["name"] = name;
        jPlayer["attack"] = 1;
        jPlayer["defense"] = 1;
        jPlayer["shieldDefense"] = 1;
        jPlayer["mana"] = 5;
        jPlayer["stamina"] = 5;
        jPlayer["hp"] = 10;
        jPlayer["xp"] = 0;
        jPlayer["level"] = 1;
        jPlayer["goal"] = 10;
        jPlayer["attacks"].append(1);
        jPlayer["attacks"].append(2);
        jPlayer["items"].append(0);
        jPlayer["items"].append(1);

        // We write the new data to a file.

        Json::StyledWriter writer;

        ofstream ofs("./json/player.json");

        ofs << writer.write(jPlayer);
        ofs.close();
    }

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

    // Itereates trough the array "items", which contains all the indexes of the items of the player
    for (const Json::Value& item : jPlayer["items"]) { // "item" is the current index
        player.items.push_back(parseItem(item.asInt())); // Pushes the item to the vector
    }

    return player;
}

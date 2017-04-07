#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <json/value.h>
#include <json/reader.h>
#include "entities.h"

Json::Value getJsonPlayer();

int getEnemiesNumber();

Attack parseAttack(int index);

Enemy parseEnemy(int index);

Player parsePlayer();

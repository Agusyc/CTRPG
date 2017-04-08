#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <json/value.h>
#include <json/reader.h>
#include "objects.h"

Json::Value getJsonPlayer();

int getItemsNumber();

int getEnemiesNumber();

Item parseItem(int index);

Attack parseAttack(int index);

Enemy parseEnemy(int index);

Player parsePlayer();

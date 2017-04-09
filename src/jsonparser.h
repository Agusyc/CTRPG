#include <fstream>
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>
#include <sys/stat.h>
#include "objects.h"
#include "utils.h"

Json::Value getJsonPlayer();

int getItemsNumber();

int getEnemiesNumber();

Item parseItem(int index);

Attack parseAttack(int index);

Enemy parseEnemy(int index);

Player parsePlayer();

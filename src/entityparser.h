#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <json/value.h>
#include <json/reader.h>
#include "entities.h"

Attack parseAttack(int index);

Enemy parseEnemy(int index);

Player parsePlayer();

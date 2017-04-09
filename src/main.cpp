#include "battle.h"
#include "objects.h"
#include "jsonparser.h"

using namespace std;

// This struct represents the player's character
Player player;

// This one represents an enemy
Enemy enemy;

// Initializes eveything
void init() {
    srand(time(NULL));

    player = parsePlayer();
}

int main() {
    init();

    while (true) {
        bool goodEnemy = false;
        while (!goodEnemy) {
            enemy = parseEnemy(rand() % getEnemiesNumber());
            // Check if the player's level is right for the enemy. Otherwise, get another one (Run loop again).
            if (player.level >= enemy.minLevel && player.level <= enemy.maxLevel) {
                goodEnemy = true; // Exit the while loop
            }
        }

        Battle testBattle(enemy, player);

        player =testBattle.start("Are you ready?");
    }
    return 0;
}

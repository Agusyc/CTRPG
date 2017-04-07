#include "battle.h"
#include "entities.h"
#include "entityparser.h"

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

	printMessage("Welcome to CTRPG!");

	while (true) {
		enemy = parseEnemy(rand() % getEnemiesNumber());

		Battle testBattle(enemy, player);

		testBattle.start("Are you ready?");
	}
	return 0;
}

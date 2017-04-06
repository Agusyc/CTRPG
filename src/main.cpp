#include "battle.h"
#include "entities.h"
#include "entityparser.h"

using namespace std;

// This struct represents the player's character
Player player;

// Enemy for testing purposes
Enemy enemy;

// Initializes eveything
void init() {
	player = parsePlayer();

	enemy = parseEnemy(0);
}

int main() {
	init();

	printMessage("Welcome to CTRPG!");

	// Just for testing the battle system
	Battle testBattle(enemy, player);

	testBattle.start("This is a test!");

	return 0;
}

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
	Attack SuperPunch = parseAttack(1);

	// parsePlayer();

	// parseEnemy(1);
}

int main() {
	init();

	printMessage("Welcome to CTRPG!");

	// Just for testing the battle system
	Battle testBattle(enemy, player);

	testBattle.start("This is a test!");

	return 0;
}

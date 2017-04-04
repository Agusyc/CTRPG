#include "battle.h"

Battle::Battle(Enemy enm, Player ply) {
  enemy = enm;
  player = ply;
}

void Battle::start(string message) {
  printMessage(message);

  printMessage(enemy.name + string(" wants to fight!"));

  loop();
}

void Battle::loop() {
  while (!over) {
    if (playerTurn) {
      switch(showMenu()) {
      case 1:
	// TODO: Show attacks menu
	break;
      case 2:
	// TODO: Make bool defending and set to true here
	break;
      case 3:
	// TODO: Show items menu
	break;
      case 4:
	// TODO: See if player can flee
	break;
      case default:
	printMessage("That is not a valid option...");
	continue;
      }
      playerTurn = !playerTurn;
    }
  }
}

int Battle:showMenu() {
  cout << "1. Attack" << endl << "2. Defend" << endl << "3. Item" << endl << "4. Flee" << endl << "Your choice: ";
												  
  int choice;
  cin >> choice;
  return choice;					
}

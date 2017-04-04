#include "battle.h"

Battle::Battle(Enemy enm, Player ply) {
  enemy = enm;
  player = ply;
}

void Battle::start(string message) {
  // Start the battle

  printMessage(message);

  printMessage(enemy.name + string(" wants to fight!"));

  loop();
}

void Battle::loop() {
  while (!over) {
    if (playerTurn) {
      // Checks the user response from the menu
      switch(showMenu()) {
      case 1:
	printMessage("You attack!", QUICK_TEXT);
	attack();
	break;
      case 2:
	defending = true;
	printMessage("You use your shield to, like, defend yourself");
	break;
      case 3:
	// TODO: Show items menu
	printMessage("You wanna use your stuff?");
	break;
      case 4:
	// TODO: See if player can flee
	printMessage("Chicken!", QUICK_TEXT);
	break;
      default:
	printMessage("That is not a valid option...");
	continue;
      }
    } else {
      attack();
    }
	playerTurn = !playerTurn;
  }

  // TODO: The battle is over:
  clearScreen();
}

int Battle::showMenu() {
  cout << "1. Attack" << endl << "2. Defend" << endl << "3. Item" << endl << "4. Flee" << endl << "Your choice: ";

  int choice;
  cin >> choice;

  cout << endl;

  return choice;
}

void Battle::attack() {
  if (playerTurn) {
    // The player attacks.

    cout << "Attacks: " << endl;

    for (unsigned int i = 0; i < player.attacks.size(); i++) {
      cout << i+1 << ". " << player.attacks.at(i).name << endl;
    }

    cout << "Your choice: ";

    int choice;
    cin >> choice;

    cout << endl;

    Attack attack = player.attacks.at(choice - 1);

    int damage = (attack.damage + attack.magicDamage + player.attack) - enemy.defense;

    stringstream ss;
    ss << "You deal " << damage << " to " << enemy.name << " with " << attack.name  << "!" << endl << "It now has " << enemy.hp - damage << " HP." << endl;

    printMessage(ss.str(), QUICK_TEXT);

    enemy.hp -= damage;
  } else {
    stringstream ss;
    ss << enemy.name << " has to attack!";

    printMessage(ss.str());
    
    bool enemyAttacks = rand() & 2;
    if (enemyAttacks) {
	int randNum = rand()%(1-0 + 1) + 0;
	Attack attack = enemy.attacks.at(randNum);

	int damage = (attack.damage + attack.magicDamage + enemy.attack) - player.defense;

	if (defending)
	  damage -= player.shieldDefense;

	bool critical = false;
	// 5 % chance of a critical hit
        randNum = rand() % 100;
	if (randNum < 5) {
	  critical = true;
	  damage *= 2;
	}
	
	ss.str("");
	ss.clear();

	if (critical)
	  ss << "With a critical hit, ";
	ss << enemy.name << " deals you " << damage << " with " << attack.name << "!"  << endl << "You now have " << player.hp - damage << " HP.";

	printMessage(ss.str(), QUICK_TEXT);

	player.hp -= damage;
    } else {
	printMessage("But it is resting...");
    }
  }

  if (enemy.hp <= 0) {
    printMessage("You win!");
    over = true;
    if (player.xp + enemy.xp < player.goal) {
      player.xp += enemy.xp;
    } else if (player.xp + enemy.xp >= player.goal) {
      stringstream ss;

      ss << "You leveled up! You are on level " << player.level + 1 << " now!";

      player.xp = player.goal - player.xp;

      printMessage(ss.str());

      player.level++;
    }
  }

  if (player.hp <= 0) {
    printMessage("You lose!");
    over = true;
  }
}

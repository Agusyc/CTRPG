#include "battle.h"

using namespace std;

Battle::Battle(Enemy enm, Player ply) {
  enemy = enm;
  player = ply;
}

void Battle::start(string message) {
  // Start the battle

  printMessage(message, YELLOW);

  printMessage(enemy.name + string(" wants to fight!"), RED);

  // Seed the random number generator.
  srand(time(NULL));

  loop();
}

void Battle::loop() {
  // Run this loop until the user loses or wins
  while (!over) {
    if (playerTurn) {
      // Checks the user response from the menu
      switch(showMenu()) {
      case 1:
	attack();
	break;
      case 2:
	defending = true;
	printMessage(string("You use your ") + YELLOW + string("shield ") + WHITE + string("to, like, defend yourself."));
	break;
      case 3:
	// TODO: Show items menu
	printMessage("You wanna use your stuff? You can't... Until I update this game.");
	continue;
      case 4:
	int chance;
	// If player has more than 50 % of his health
	if (player.hp >= (parsePlayer().hp / 2)) {
		chance = 75; // 75% chance of fleeing
	} else {
		chance = 32; // 32% chance of fleeing
	}
	// See if the player flees or not
	if (rand() % 100 < chance) {
		printMessage("You escape... You chicken!");
		over = true;
		continue;
	} else {
		printMessage("You tried to escape... But you couldn't!");
	}
	break;
      default:
	printMessage("That is not a valid option...");
	continue;
      }
    } else {
      // The enemy attacks
      attack();
    }
    // Pass to the next turn
    playerTurn = !playerTurn;
  }

  clearScreen();
}

int Battle::showMenu() {
  cout << "1. Attack" << endl << "2. Defend" << endl << "3. Item" << endl << "4. Flee" << endl << "HP: " << GREEN << player.hp << WHITE << " | Mana: " << GREEN << player.mana << WHITE << endl << "Your choice: ";

  int choice;
  cin >> choice;

  cout << endl;

  return choice;
}

void Battle::attack() {
  unsigned int choice;
  if (playerTurn) {
    // The player attacks.
    bool exitLoop = false;
    Attack attack;

    while (!exitLoop) {
      cout << "Attacks: " << endl;

      for (unsigned int i = 0; i < player.attacks.size(); i++) {
	cout << i+1 << ". " << player.attacks.at(i).name << endl;
      }

      cout << "Your choice: ";

      cin >> choice;

      cout << endl;

      if (choice > player.attacks.size() || choice < 0) {
	printMessage("That's not a valid choice...");
	cout << endl;
	continue;
      }

      attack = player.attacks.at(choice - 1);

      if (player.mana < attack.mana) {
	printMessage(string("You don't have enough ") + GREEN + string("mana ") + WHITE + string("to use that attack!"));
	continue;
      }

      if (player.stamina < attack.stamina) {
	printMessage(string("You don't have enough ") + GREEN + string("stamina ") + WHITE + string("to use that attack!"));
	continue;
      }

      exitLoop = true;
    }

    // Decrease the user mana and stamina
    player.mana -= attack.mana;
    player.stamina -= attack.stamina;

    // Calculate how much damage is dealt to the enemy
    int damage = (attack.damage + attack.magicDamage + player.attack) - enemy.defense;
    
    if (damage <= 0) {
      // The attack doesn't do anything
      printMessage("Man... That attack is so lame that it doesn't do anything.");
    } else {
      // The attack is powerful enough to do something
      bool critical = false;
      // 5 % chance of a critical hit
      if (rand() % 100 < 5) {
	critical = true;
	damage *= 2;
      }
      
      stringstream ss;
      if (critical)
	ss << "With a " << BOLD << "critical hit, ";
      ss << "You deal " << RED << damage << WHITE << " to " << YELLOW << enemy.name << WHITE << " with " << YELLOW << attack.name << WHITE  << "!" << endl << "It now has " << GREEN << enemy.hp - damage << WHITE << " HP." << endl;
      
      printMessage(ss.str(), WHITE, QUICK_TEXT);
      
      enemy.hp -= damage;
    }
  } else {
    // The enemy attacks
    stringstream ss;
    ss << RED << enemy.name << WHITE << " has to attack!";
    
    printMessage(ss.str());
    
    bool enemyAttacks = rand() % 2;
    if (enemyAttacks) {
      Attack attack;
      bool exitLoop = false;
      
      // This loop ensures that the enemy doesn't choose an attack that it can't use because of mana or stamina.
      while (!exitLoop) {
	attack = enemy.attacks.at(rand() % getAttacksNumber(enemy.id));
	
	if (enemy.mana >= attack.mana && enemy.stamina >= attack.stamina) {
	  exitLoop = true;
	}
      }
      
      // Decrease enemy's mana and stamina
      enemy.mana -= attack.mana;
      enemy.stamina -= attack.stamina;
      
      // Calculate how much damage is dealt to the player
      int damage = (attack.damage + attack.magicDamage + enemy.attack) - player.defense;

      if (defending)
	damage -= player.shieldDefense;

      if (damage <= 0) {
	// The attack doesn't do anything
	ss << enemy.name << " tries to hurt you with " << attack.name <<  "... But it can't!";
	printMessage(ss.str());
      } else {
	// The attack is powerful enough...
	bool critical = false;
	// 5 % chance of a critical hit
	if (rand() % 100 < 5) {
	  critical = true;
	  damage *= 2;
	}

	// Reset the stringstream
	ss.str("");
	ss.clear();

	if (critical)
	  ss << "With a critical hit, ";
ss << RED << enemy.name << WHITE << " deals you " << RED << damage << WHITE << " with " << YELLOW << attack.name << WHITE << "!"  << endl << "You now have " << GREEN << player.hp - damage << WHITE << " HP." << endl;

	printMessage(ss.str(), WHITE, QUICK_TEXT);

	player.hp -= damage;
      }
    } else {
      // The enemy decides not to attack
      printMessage("But it is resting...");
    }
  }

  // When the player wins
  if (enemy.hp <= 0) {
    printMessage("You win!");
    over = true;
    if (player.xp + enemy.xp < player.goal) {
      player.xp += enemy.xp;
    } else if (player.xp + enemy.xp >= player.goal) {
      stringstream ss;

      ss << "You leveled up! You are on level " << YELLOW << player.level + 1 << WHITE << " now!";

      player.xp = player.goal - player.xp;

      printMessage(ss.str());

      player.level++;
      player.goal *= 2;

      // To let the user choose what stats to improve
      showLevelUpMenu(parsePlayer());
    }
  }

  // When the enemy wins
  if (player.hp <= 0) {
    printMessage("You lose!");
    over = true;
    exit(0);
  }
}

void Battle::showLevelUpMenu(Player originalPlayer) {
  for (int points = player.level; points != 0; points--) {
    cout << "Points: " << points << endl << "1. HP" << endl << "2. Attack" << endl << "3. Defense" << endl << "4. Shield" << endl << "5. Mana" << endl << "6. Stamina" << endl << "Your choice: ";

    int choice;

    cin >> choice;

    switch (choice) {
    case 1:
      originalPlayer.hp++;
      break;
    case 2:
      originalPlayer.attack++;
      break;
    case 3:
      originalPlayer.defense++;
      break;
    case 4:
      originalPlayer.shieldDefense++;
      break;
    case 5:
      originalPlayer.mana++;
      break;
    case 6:
      originalPlayer.stamina++;
      break;
    }
  }

  Json::Value jPlayer = getJsonPlayer();

  jPlayer["hp"] = originalPlayer.hp;
  jPlayer["attack"] = originalPlayer.attack;
  jPlayer["defense"] = originalPlayer.defense;
  jPlayer["shieldDefense"] = originalPlayer.shieldDefense;
  jPlayer["mana"] = originalPlayer.mana;
  jPlayer["stamina"] = originalPlayer.stamina;
  jPlayer["goal"] = player.goal;
  jPlayer["xp"] = player.xp;
  jPlayer["level"] = player.level;

  Json::StyledWriter writer;
  ofstream jPlayerFile("./json/player.json");
  jPlayerFile << writer.write(jPlayer);
}

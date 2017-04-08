#include "battle.h"

using namespace std;

Battle::Battle(Enemy enm, Player ply) {
  enemy = enm;
  player = ply;
}

Player Battle::start(string message) {
  // Start the battle

  printMessage(message, YELLOW);

  printMessage(RED + enemy.name + WHITE + string(" wants to fight!"));

  // Seed the random number generator.
  srand(time(NULL));

  loop();

  return player;
}

void Battle::loop() {
  // Run this loop until the user loses or wins
  while (!over) {
    if (playerTurn) {
      // Checks the user response from the menu
      switch(showMenu()) {
      case 1:
	if (attack() == 1) {
		continue;
	}
	break;
      case 2:
	defending = true;
	printMessage(string("You use your ") + YELLOW + string("shield ") + WHITE + string("to, like, defend yourself."));
	break;
      case 3:
	if (useItem() == 1) {
		continue;
	}
	break;
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
		writeItems();
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

int Battle::attack() {
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

      cout << player.attacks.size() + 1 << ". Go back" << endl;

      cout << "Your choice: ";

      cin >> choice;

      cout << endl;

      if (choice == player.attacks.size() + 1) {
	return 1;
      }

      if (choice > player.attacks.size() || choice < 1) {
	printMessage("That's not a valid choice...");
	cout << endl;
	continue;
      }

      attack = player.attacks.at(choice - 1);

      if (player.mana < attack.mana) {
	printMessage(string("You don't have enough ") + YELLOW + string("mana ") + WHITE + string("to use that attack!"));
	continue;
      }

      if (player.stamina < attack.stamina) {
	printMessage(string("You don't have enough ") + YELLOW + string("stamina ") + WHITE + string("to use that attack!"));
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
      ss << "You deal " << GREEN << damage << WHITE << " to " << RED << enemy.name << WHITE << " with " << YELLOW << attack.name << WHITE  << "!" << endl << "It now has " << GREEN << enemy.hp - damage << WHITE << " HP." << endl;
      
      printMessage(ss.str());
      
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
	attack = enemy.attacks.at(rand() % enemy.attacks.size());
	
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
	ss << RED << enemy.name << WHITE << " tries to hurt you with " << YELLOW << attack.name << WHITE <<  "... But it can't!";
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
ss << RED << enemy.name << WHITE << " deals you " << GREEN << damage << WHITE << " with " << YELLOW << attack.name << WHITE << "!"  << endl << "You now have " << GREEN << player.hp - damage << WHITE << " HP." << endl;

	printMessage(ss.str());

	player.hp -= damage;
      }
    } else {
      // The enemy decides not to attack
      printMessage("But it is resting...\n");
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
    // Give the player a random Item:
    Item item;

    bool exitLoop = false;
    while (!exitLoop) {
	item = parseItem(rand() % getItemsNumber());
	if (player.level < item.minLevel || player.level > item.maxLevel) {
		continue;
	}

	exitLoop = true;
    }

    player.items.push_back(item);

    printMessage(string("You found ") + YELLOW + item.name + WHITE + string("!"));

    writeItems();
  }

  // When the enemy wins
  if (player.hp <= 0) {
    printMessage("You lose!");
    over = true;
    exit(0);
  }
  return 0;
}

int Battle::useItem() {
	unsigned int choice;
	bool exitLoop = false;
	while (!exitLoop) {
		for (unsigned int i = 0; i < player.items.size(); i++) {
			cout << i + 1 << ". " << player.items.at(i).name << endl;
		}
		
		cout << player.items.size() + 1 << ". Go back" << endl;

		cout << "Your choice: ";

 	 	cin >> choice;

		cout << endl;

		if (choice == player.items.size() + 1) {
			return 1;
		}

		if (choice > player.items.size() || choice < 1) {
        		printMessage("That's not a valid choice...");
	        	cout << endl;
        		continue;
		}

		exitLoop = true;
	}

 	Item item = player.items.at(choice - 1);

  	stringstream ss;

  	ss << "The item " << YELLOW << item.name << WHITE << ":" << endl; 

  	if (item.attackBoost != 0) {
		ss << "Boosts your attack by " << GREEN << item.attackBoost << WHITE << endl;
		player.attack += item.attackBoost;
  	}

  	if (item.defenseBoost != 0) {
		ss << "Boosts your defense by " << GREEN << item.defenseBoost << WHITE << endl;
		player.defense += item.defenseBoost;
  	}

  	if (item.manaRecover != 0) {
		ss << "Gives you " << GREEN << item.manaRecover << WHITE << " mana." << endl;
		player.mana += item.manaRecover;
  	}

  	if (item.staminaRecover != 0) {
		ss << "Gives you " << GREEN << item.staminaRecover << WHITE << " stamina." << endl;	
 		player.stamina += item.staminaRecover;
  	}

  	if (item.hpRecover != 0) {
		ss << "Gives you " << GREEN << item.hpRecover << WHITE << " HP." << endl;
 		player.hp += item.hpRecover;
  	}

  	cout << ss.str() << endl;

	player.items.erase(player.items.begin() + item.id); // Delete item with index "item.id"

	return 0;
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
  jPlayer["mana"] = originalPlayer.mana;
  jPlayer["stamina"] = originalPlayer.stamina;
  jPlayer["goal"] = player.goal;
  jPlayer["xp"] = player.xp;
  jPlayer["level"] = player.level;

  Json::StyledWriter writer;
  ofstream jPlayerFile("./json/player.json");
  jPlayerFile << writer.write(jPlayer);
}

void Battle::writeItems() {
	Json::Value newArray;
	Json::Value jPlayer = getJsonPlayer();

	for(vector<Item>::iterator it = player.items.begin(); it != player.items.end(); ++it) {
		Item item = *it;
		newArray.append(item.id);
	}

	jPlayer["items"] = newArray;

	Json::StyledWriter writer;
	ofstream jPlayerFile("./json/player.json");
	jPlayerFile << writer.write(jPlayer);
}
